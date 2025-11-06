// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GA/GA_Killer_Carry_Sample.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "KMJ/Character/KillerCharacter.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Component/InteractorComponent.h"


UGA_Killer_Carry_Sample::UGA_Killer_Carry_Sample()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(DBDGameplayTags::Killer_Common_Ability_Interaction_Carry);
	ActivationRequiredTags.AddTag(DBDGameplayTags::Interactable_Character_Survivor);
	ActivationOwnedTags.AddTag(DBDGameplayTags::Killer_Common_Status_Carrying);
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::OwnedTagPresent;
	TriggerData.TriggerTag = DBDGameplayTags::Survivor_Status_Captured_Killer;
	AttachSocketName = FName("SurvivorAttach");
}

void UGA_Killer_Carry_Sample::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo,
                                              const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//Killer 존재하는지 확인
	Killer = Cast<AKillerCharacter>(ActorInfo->OwnerActor);
	if (Killer == nullptr)
	{
		UE_LOG(LogTemp,Error, TEXT("KillerActor: Nullptr"));
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}
	UE_LOG(LogTemp,Warning, TEXT("KillerActor: %s"), *Killer->GetName());
	//Killer의 InteractWithCurrentInteractable 실행
	Killer->GetInteractorComponent()->InteractWithCurrentInteractable();
	//Interact 가능한 Survivor 있는지 확인
	InteractableSurvivorCharacter = GetInteractableSurvivorCharacter();
	if (InteractableSurvivorCharacter == nullptr)
	{
		UE_LOG(LogTemp,Error, TEXT("InteractableSurvivorCharacter: Nullptr"));	
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}
	UE_LOG(LogTemp,Warning, TEXT("InteractableSurvivorCharacter: %s"), *InteractableSurvivorCharacter->GetName());
	//킬러가 현재 들고 있는 생존자에 값 할당
	Killer->SetCarriedSurvivorCharacter(InteractableSurvivorCharacter);
	InteractableSurvivorCharacter->CaptureSurvivor();

	UE_LOG(LogTemp, Warning, TEXT("UGA_Carry::ActivateAbility C++ End"));
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!ASC)
	{
		return;
	}
	// Cost, Cooldown 등을 검사 + 점프 여부 검사
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	// PredictionKey는 클라이언트가 서버의 명령 없이 예측해서 실행할 때 사용 - 애니메이션 재생 등 중요한 로직이 아닐 경우
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
	}
	
}

void UGA_Killer_Carry_Sample::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,
                                         bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_Killer_Carry_Sample::PlayLoopMontage()
{
	// PredictionKey는 클라이언트가 서버의 명령 없이 예측해서 실행할 때 사용 - 애니메이션 재생 등 중요한 로직이 아닐 경우
	if (IsActive())
	{
		if (IsLocallyControlled()&&K2_HasAuthority())
		{
			UAbilityTask_PlayMontageAndWait* PlayLoopMontageTask =
				UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
					this, NAME_None, FPVStartMontage, 1.f);
			PlayLoopMontageTask->OnBlendOut.AddDynamic(this, &UGA_Killer_Carry_Sample::K2_EndAbility);
			PlayLoopMontageTask->OnCancelled.AddDynamic(this, &UGA_Killer_Carry_Sample::K2_EndAbility);
			PlayLoopMontageTask->OnCompleted.AddDynamic(this, &UGA_Killer_Carry_Sample::K2_EndAbility);
			PlayLoopMontageTask->OnInterrupted.AddDynamic(this, &UGA_Killer_Carry_Sample::K2_EndAbility);
			PlayLoopMontageTask->ReadyForActivation();
		}
		else if (!IsLocallyControlled()&&!K2_HasAuthority())
		{
			UAbilityTask_PlayMontageAndWait* PlayLoopMontageTask =
				UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
					this, NAME_None, TPVStartMontage, 1.f);
			PlayLoopMontageTask->OnBlendOut.AddDynamic(this, &UGA_Killer_Carry_Sample::K2_EndAbility);
			PlayLoopMontageTask->OnCancelled.AddDynamic(this, &UGA_Killer_Carry_Sample::K2_EndAbility);
			PlayLoopMontageTask->OnCompleted.AddDynamic(this, &UGA_Killer_Carry_Sample::K2_EndAbility);
			PlayLoopMontageTask->OnInterrupted.AddDynamic(this, &UGA_Killer_Carry_Sample::K2_EndAbility);
			PlayLoopMontageTask->ReadyForActivation();
		}
	}
}

void UGA_Killer_Carry_Sample::AttachSurvivorCharacterToKiller(FGameplayEventData Payload)
{
	GetInteractableSurvivorCharacter()->AttachToComponent(GetOwningComponentFromActorInfo(),
	                                                      FAttachmentTransformRules::SnapToTargetNotIncludingScale,
	                                                      AttachSocketName);
}
AKillerCharacter* UGA_Killer_Carry_Sample::GetOwningKillerCharacter()
{
	return Cast<AKillerCharacter>(GetOwningActorFromActorInfo());
}
