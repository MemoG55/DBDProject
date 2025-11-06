// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/GAS/GA_Skill.h"

#include "VectorTypes.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KMJ/AbilitySystem/HuntressAttributeSet.h"
#include "KMJ/Axe/AxeComponent.h"
#include "KMJ/Character/KillerHuntress.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDGameplayTags.h"


UGA_Skill::UGA_Skill()
{
	
}
void UGA_Skill::StartChargingAxe()
{
	MinChargingTime = Huntress->HuntressAttributeSet->ChargingAxeMinRate.GetBaseValue();
	MaxChargingTime = Huntress->HuntressAttributeSet->ChargingAxeMaxRate.GetBaseValue();
	MinChargingSpeed = Huntress->HuntressAttributeSet->AxeMinSpeed.GetBaseValue();
	MaxChargingSpeed = Huntress->HuntressAttributeSet->AxeMaxSpeed.GetBaseValue();
	CurrentSpeed = MinChargingSpeed;
	CurrentChargeTime = 0.0f;
	if (Huntress && Huntress->AxeComponent)
	{
		Huntress->AxeComponent->StartChargingThrow();
	}
	// 차징 ��머 �작
	GetWorld()->GetTimerManager().SetTimer(ChargeTimerHandle, this, &UGA_Skill::UpdateChargingAxe, 0.1f, true);
}

void UGA_Skill::UpdateChargingAxe()
{
	if (CurrentChargeTime < MaxChargingTime)
	{
		CurrentChargeTime = FMath::Clamp(CurrentChargeTime + 0.1f, 0.0f, MaxChargingTime);

		// 차징 �간최소 차징 �간초과�면 �도 계산
		if (CurrentChargeTime >= MinChargingTime)
		{
			float ChargeProgress = (CurrentChargeTime - MinChargingTime) / (MaxChargingTime - MinChargingTime);

			// �형 보간�로 �도 계산 (MinChargingSpeed�서 MaxChargingSpeed�증�)
			float NewSpeed = FMath::Lerp(MinChargingSpeed, MaxChargingSpeed, ChargeProgress);
			
			UpdateAxeSpeed(NewSpeed);
		}
		else
		{
			UpdateAxeSpeed(MinChargingSpeed);
		}
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(ChargeTimerHandle);
	}
}

void UGA_Skill::UpdateAxeSpeed(float NewSpeed)
{
	CurrentSpeed = FMath::Min(MaxChargingSpeed, NewSpeed);
	Huntress->HuntressAttributeSet->AxeMaxSpeed.SetCurrentValue(CurrentSpeed);
	//Debug::Print(FString::Printf(TEXT("Current Axe Speed: %f"), CurrentSpeed), 314);
}


void UGA_Skill::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Huntress = Cast<AKillerHuntress>(GetKillerCharacterFromActorInfo());
	StartChargingAxe();
	if (UDBDBlueprintFunctionLibrary::NativeActorHasTag(Huntress, DBDGameplayTags::Killer_Huntress_Status_AxeCharging))
	{
		K2_CancelAbility();
		UDBDBlueprintFunctionLibrary::RemoveTagFromActor(Huntress, DBDGameplayTags::Killer_Huntress_Status_AxeCharging);
	}
	else
	{
		if (UDBDBlueprintFunctionLibrary::NativeActorHasTag(Huntress, DBDGameplayTags::Killer_Huntress_Status_AxeEmpty))
		{
			K2_CancelAbility();
		}
		else
		{
			if (UDBDBlueprintFunctionLibrary::NativeActorHasTag(Huntress, DBDGameplayTags::Killer_Huntress_Status_AxeFull))
			{
				UDBDBlueprintFunctionLibrary::RemoveTagFromActor(Huntress, DBDGameplayTags::Killer_Huntress_Status_AxeFull);
			}

			//몽�죤행 �그 �무기 Visibility 처리
			UDBDBlueprintFunctionLibrary::AddUniqueTagToActor(Huntress, DBDGameplayTags::Killer_Huntress_Status_AxeCharging);
			Huntress->Multicast_SetLeftAxeVisibility(true);
			CommitAbility(Handle, ActorInfo, ActivationInfo);

			float ChargingWalkingSpeed = Huntress->KillerAttributeSet->WalkingSpeed.GetBaseValue() * 0.7;
			Huntress->KillerAttributeSet->SetCurrentWalkingSpeed(ChargingWalkingSpeed);
			
			if (IsLocallyControlled())
			{
				UAbilityTask_PlayMontageAndWait* PlayLoopMontageTask =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this, NAME_None, FPVThrowInAndIdleMontage, 1.f);
				//PlayLoopMontageTask->OnBlendOut.AddDynamic(this, &UGA_Skill::K2_CancelAbility);
				PlayLoopMontageTask->OnInterrupted.AddDynamic(this, &UGA_Skill::K2_CancelAbility);
				PlayLoopMontageTask->OnCancelled.AddDynamic(this, &UGA_Skill::K2_CancelAbility);
				PlayLoopMontageTask->ReadyForActivation();
			}
			else
			{
				UAbilityTask_PlayMontageAndWait* PlayLoopMontageTask =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this, NAME_None, TPVThrowInAndIdleMontage, 1.f);
				//PlayLoopMontageTask->OnBlendOut.AddDynamic(this, &UGA_Skill::K2_CancelAbility);
				PlayLoopMontageTask->OnInterrupted.AddDynamic(this, &UGA_Skill::K2_CancelAbility);
				PlayLoopMontageTask->OnCancelled.AddDynamic(this, &UGA_Skill::K2_CancelAbility);
				PlayLoopMontageTask->ReadyForActivation();
			}
			
		}
	}
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGA_Skill::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	if (!IsActive() && !bIsCoolDown && Huntress->HuntressAttributeSet->AxeNumber.GetCurrentValue() > 0)
	{
		K2_ActivateAbility();
	}
}

void UGA_Skill::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	K2_EndAbility();
}

void UGA_Skill::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                           const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!bWasCancelled)
		if (Huntress && Huntress->AxeComponent)
			Huntress->AxeComponent->StopChargingThrow();
	float NewWalkingSpeed = Huntress->KillerAttributeSet->WalkingSpeed.GetBaseValue();
	Huntress->KillerAttributeSet->SetCurrentWalkingSpeed(NewWalkingSpeed);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	Huntress->Multicast_SetLeftAxeVisibility(false);
}

