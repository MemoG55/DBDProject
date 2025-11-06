// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GA/Interaction/GA_Survivor_Rescue.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/DataAsset/DA_SurvivorMontage.h"
#include "JMS/GAS/SurvivorAbilitySystemComponent.h"
#include "JMS/GAS/SurvivorAttributeSet.h"
#include "JMS/GAS/GA/Interaction/GA_Survivor_OpenExitDoor.h"
#include "Kismet/KismetMathLibrary.h"
#include "MMJ/Object/Component/IC_Hook.h"
#include "MMJ/Object/Interactable/Obj_Hook.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Component/DBDMotionWarpingComponent.h"
#include "Shared/Component/InteractorComponent.h"


UGA_Survivor_Rescue::UGA_Survivor_Rescue()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(DBDGameplayTags::Survivor_Ability_Interaction_Rescue);
	ActivationRequiredTags.AddTag(DBDGameplayTags::Interactable_Object_Hook);
	ActivationOwnedTags.AddTag(DBDGameplayTags::Survivor_Status_MoveDisabled);
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
}


void UGA_Survivor_Rescue::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	bIsRescueSucceed = false;

	// Cost, Cooldown 등을 검사 + 점프 여부 검사
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	float RescueSpeed = 1.0f;
	USurvivorAbilitySystemComponent* SurvivorASC = GetSurvivorAbilitySystemComponentFromActorInfo();
	if (SurvivorASC)
	{
		RescueSpeed = SurvivorASC->GetNumericAttribute(USurvivorAttributeSet::GetRescueSpeedAttribute());
		if (RescueSpeed <= 0)
		{
			RescueSpeed = 1.0f;
		}
	}

	if (K2_HasAuthority())
	{
		float AnimDuration = GetSurvivorCharacterFromActorInfo()->PlaySyncMontageFromServer(
			GetSurvivorCharacterFromActorInfo()->SurvivorMontageData->RescueIn, RescueSpeed);
		GetWorld()->GetTimerManager().SetTimer(RescueTimerHandle, this, &UGA_Survivor_Rescue::OnRescueSucceed,
		                                       AnimDuration / RescueSpeed, false);
		GetSurvivorCharacterFromActorInfo()->MoveEnabled(false);
		if (AObj_Hook* CachedHook = GetCachedCurrentInteractable<AObj_Hook>())
		{
			UIC_Hook* HookIC = Cast<UIC_Hook>(CachedHook->GetInteractableComponent());
			CachedCapturedSurvivor = Cast<ASurvivorCharacter>(HookIC->GetCapturedActor());
			if (CachedCapturedSurvivor)
			{
				CachedCapturedSurvivor->PlaySyncMontageFromServer(
					GetSurvivorCharacterFromActorInfo()->SurvivorMontageData->RescuedByOtherIn, RescueSpeed);
			}
			UDBDBlueprintFunctionLibrary::MoveDBDCharacterToMeshSocket(
				CachedHook->GetSkeletalMeshComponent(), FName(TEXT("socket_KillerAttach")),
				GetSurvivorCharacterFromActorInfo());
		}
		Client_StartWidgetUpdate(AnimDuration, RescueSpeed);
	}
	LookAt(CachedCapturedSurvivor);
}

void UGA_Survivor_Rescue::InputReleased(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo,
                                       const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	if (IsActive())
	{
		K2_EndAbility();
	}
}


void UGA_Survivor_Rescue::OnRescueSucceed()
{
	if (IsActive())
	{
		InteractStart();
		GetSurvivorCharacterFromActorInfo()->PlaySyncMontageFromServer(
			GetSurvivorCharacterFromActorInfo()->SurvivorMontageData->RescueOut);
		if (CachedCapturedSurvivor)
		{
			CachedCapturedSurvivor->PlaySyncMontageFromServer(
				CachedCapturedSurvivor->SurvivorMontageData->RescuedByOtherOut);
			CachedCapturedSurvivor->SendGameplayTagEventToSelf(DBDGameplayTags::Survivor_Event_RescueFromHook,
			                                                   FGameplayEventData());
		}
		bIsRescueSucceed = true;
	}
}

bool UGA_Survivor_Rescue::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayTagContainer* SourceTags,
                                            const FGameplayTagContainer* TargetTags,
                                            FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	UInteractorComponent* InteractorComponent = GetInteractorComponentFromActorInfo();
	if (InteractorComponent)
	{
		if (AObj_Hook* Hook = GetCurrentInteractable<AObj_Hook>())
		{
			if (UAbilitySystemComponent* HookASC = Hook->GetAbilitySystemComponent())
			{
				FGameplayTagContainer AllowTags;
				AllowTags.AddTag(DBDGameplayTags::Object_Status_IsActive);

				if (HookASC->HasAllMatchingGameplayTags(AllowTags))
				{
					return true;
				}
			}
		}
	}
	return false;
}


void UGA_Survivor_Rescue::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                                    bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if (K2_HasAuthority())
	{
		GetSurvivorCharacterFromActorInfo()->StopSyncMontageFromServer(
			GetSurvivorCharacterFromActorInfo()->SurvivorMontageData->RescueIn);
		GetWorld()->GetTimerManager().ClearTimer(RescueTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(RescueWidgetTimerHandle);
		if (CachedCapturedSurvivor)
		{
			CachedCapturedSurvivor->StopSyncMontageFromServer(
				GetSurvivorCharacterFromActorInfo()->SurvivorMontageData->RescuedByOtherIn);
		}
	}
	GetSurvivorCharacterFromActorInfo()->MoveEnabled(true);
}

void UGA_Survivor_Rescue::UpdateProgressPercentageByDeltaProgress(float DeltaProgress)
{
	ProgressPercentage += DeltaProgress;
}

void UGA_Survivor_Rescue::Client_StartWidgetUpdate_Implementation(float AnimDuration, float RescueSpeed)
{
	if (IsActive())
	{
		float DeltaProgress = RescueSpeed / AnimDuration * WidgetUpdateInterval;
		RescueWidgetTimerDelegate = FTimerDelegate::CreateUObject(
			this, &UGA_Survivor_Rescue::UpdateProgressPercentageByDeltaProgress,
			DeltaProgress);
		GetWorld()->GetTimerManager().SetTimer(RescueWidgetTimerHandle, RescueWidgetTimerDelegate,
		                                       WidgetUpdateInterval, true);
	}
}
