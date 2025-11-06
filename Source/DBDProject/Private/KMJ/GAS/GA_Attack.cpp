// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/GAS/GA_Attack.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/GameSession.h"
#include "JMS/GAS/GA/GA_Killer_Carry_Sample.h"
#include "Kismet/KismetSystemLibrary.h"
#include "KMJ/Character/KillerCharacter.h"
#include "Net/UnrealNetwork.h"


UGA_Attack::UGA_Attack()
{
	// 기본적으로 능력은 비활성화
	//bIsCoolDown = false;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_Attack::IncreaseSpeed()
{
	Speed = FMath::Clamp(Speed + 0.1f, 1.f, 3.f);

	// ✅ 디버깅용
	UE_LOG(LogTemp, Log, TEXT("Speed: %f"), Speed);

	if (Speed >= 2.f)
	{
		// 목표 속도 도달 시 타이머 정지
		GetWorld()->GetTimerManager().ClearTimer(SpeedIncreaseTimerHandle);
	}
}

void UGA_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Killer = GetKillerCharacterFromActorInfo();

	//CoolDown Check
	if (bIsCoolDown) K2_CancelAbility();

	bIsCoolDown = true;
	Killer->DisableInput(Cast<APlayerController>(Killer->GetController()));


	Speed = 1.f;
	GetWorld()->GetTimerManager().SetTimer(SpeedIncreaseTimerHandle, this, &UGA_Attack::IncreaseSpeed, 0.01f, true);
	
	if (IsLocallyControlled())
	{
		UAbilityTask_PlayMontageAndWait* PlayLoopMontageTask =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this, NAME_None, FPVAttackInMontage, 1.f);
		PlayLoopMontageTask->OnCompleted.AddDynamic(this, &UGA_Attack::CallBeforeEndAbility);
		PlayLoopMontageTask->OnBlendOut.AddDynamic(this, &UGA_Attack::CallBeforeEndAbility);
		PlayLoopMontageTask->OnInterrupted.AddDynamic(this, &UGA_Attack::K2_CancelAbility);
		PlayLoopMontageTask->OnCancelled.AddDynamic(this, &UGA_Attack::K2_CancelAbility);
		PlayLoopMontageTask->ReadyForActivation();
	}
	else
	{
		UAbilityTask_PlayMontageAndWait* PlayLoopMontageTask =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this, NAME_None, TPVAttackInMontage, 1.f);
		PlayLoopMontageTask->OnCompleted.AddDynamic(this, &UGA_Attack::CallBeforeEndAbility);
		PlayLoopMontageTask->OnBlendOut.AddDynamic(this, &UGA_Attack::CallBeforeEndAbility);
		PlayLoopMontageTask->OnInterrupted.AddDynamic(this, &UGA_Attack::K2_CancelAbility);
		PlayLoopMontageTask->OnCancelled.AddDynamic(this, &UGA_Attack::K2_CancelAbility);
		PlayLoopMontageTask->ReadyForActivation();
	}
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGA_Attack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	if (!IsActive())
	{
		K2_ActivateAbility();
	}
}

void UGA_Attack::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	if (!IsActive())
	{
		CallBeforeEndAbility();
		K2_EndAbility();
	}
}

void UGA_Attack::CallBeforeEndAbility()
{
	if (!IsActive()) K2_CancelAbility();
	GetWorld()->GetTimerManager().ClearTimer(SpeedIncreaseTimerHandle);
	Launch();

	if (IsLocallyControlled())
	{
		PlayMontage(FPVAttackMontage);
	}
	else
	{
		PlayMontage(TPVAttackMontage);
	}
}

void UGA_Attack::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UGA_Attack, bIsCoolDown, COND_None, REPNOTIFY_Always);
}

void UGA_Attack::PlayMontage(UAnimMontage* Montage)
{
	UAbilityTask_PlayMontageAndWait* PlayLoopMontageTask =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this, NAME_None, Montage, 1.f);
	PlayLoopMontageTask->OnCompleted.AddDynamic(this, &UGA_Attack::K2_EndAbility);
	PlayLoopMontageTask->OnBlendOut.AddDynamic(this, &UGA_Attack::K2_EndAbility);
	PlayLoopMontageTask->OnInterrupted.AddDynamic(this, &UGA_Attack::K2_CancelAbility);
	PlayLoopMontageTask->OnCancelled.AddDynamic(this, &UGA_Attack::K2_CancelAbility);
	PlayLoopMontageTask->ReadyForActivation();
}

void UGA_Attack::Launch()
{
	if (Killer && Killer->GetCharacterMovement())
	{
		FVector LaunchVelocity = Killer->GetActorForwardVector() * Speed * 300.f; 
		Killer->LaunchCharacter(LaunchVelocity, true, false); 
	}
}

void UGA_Attack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                            const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	bIsCoolDown = false;
	Killer->EnableInput(Cast<APlayerController>(Killer->GetController()));
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
