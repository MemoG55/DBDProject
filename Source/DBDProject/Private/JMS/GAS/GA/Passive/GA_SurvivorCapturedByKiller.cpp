// Fill out your copyright notice in the Description page of Project Settings.
// IN -> PickUp -> Loop 순으로 애니메이션을 실행합니다.
// Active하지 않으면 End로 갑니다(탈출하거나 취소되었을 경우)
// TODO: Loop중에 스킬체크를 실행
#include "JMS/GAS/GA/Passive/GA_SurvivorCapturedByKiller.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/Component/SkillCheckComponent.h"
#include "KMJ/Character/KillerCharacter.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Component/InteractableComponent.h"
#include "Shared/Subsystem/DBDCharacterObserver.h"


UGA_SurvivorCapturedByKiller::UGA_SurvivorCapturedByKiller()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(DBDGameplayTags::Survivor_Ability_Passive_CapturedByKiller);
	ActivationOwnedTags.AddTag(DBDGameplayTags::Survivor_Status_MoveDisabled);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::OwnedTagAdded;
	TriggerData.TriggerTag = DBDGameplayTags::Survivor_Status_Captured;
	AbilityTriggers.Add(TriggerData);
}

void UGA_SurvivorCapturedByKiller::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                   const FGameplayAbilityActorInfo* ActorInfo,
                                                   const FGameplayAbilityActivationInfo ActivationInfo,
                                                   const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!ASC)
	{
		return;
	}
	CachedInteractableComponent = GetInteractableComponentFromActorInfo();
	if (!CachedInteractableComponent)
	{
		return;
	}

	// PredictionKey는 클라이언트가 서버의 명령 없이 예측해서 실행할 때 사용 - 애니메이션 재생 등 중요한 로직이 아닐 경우
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		GetSurvivorCharacterFromActorInfo()->SetCollisionAndGravityEnabled(false);
		UAbilityTask_PlayMontageAndWait* PlayPickUpInMontageTask =
			UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
				this, NAME_None, PickUpInMontage, 1.f);
		PlayPickUpInMontageTask->OnBlendOut.AddDynamic(this, &UGA_SurvivorCapturedByKiller::K2_EndAbility);
		PlayPickUpInMontageTask->OnCancelled.AddDynamic(this, &UGA_SurvivorCapturedByKiller::K2_EndAbility);
		PlayPickUpInMontageTask->OnCompleted.AddDynamic(this, &UGA_SurvivorCapturedByKiller::K2_EndAbility);
		PlayPickUpInMontageTask->OnInterrupted.AddDynamic(this, &UGA_SurvivorCapturedByKiller::K2_EndAbility);
		PlayPickUpInMontageTask->ReadyForActivation();
		UDBDCharacterObserver* CharacterObserver = GetWorld()->GetSubsystem<UDBDCharacterObserver>();
		if (CharacterObserver)
		{
			CachedKillerCharacter = CharacterObserver->GetKiller();
			if (CachedKillerCharacter)
			{
				UDBDBlueprintFunctionLibrary::AttachCharacterWithRotationAdjust(
					CachedKillerCharacter->GetMesh(), FName("joint_Char"), GetSurvivorCharacterFromActorInfo(),
					FRotator(0, -90, 0));
			}
		}
	}
}

void UGA_SurvivorCapturedByKiller::PlayPickUpMontage()
{
	if (IsActive())
	{
		UAbilityTask_WaitGameplayEvent* WaitGameplayEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
			this, DBDGameplayTags::Object_Event_Check);
		{
		}
	}
}


void UGA_SurvivorCapturedByKiller::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo,
                                              const FGameplayAbilityActivationInfo ActivationInfo,
                                              bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if (GetAnimInstance())
	{
		GetAnimInstance()->StopAllMontages(0.1f);
	}
	if (bWasCancelled)
	{
		GetSurvivorCharacterFromActorInfo()->SetCollisionAndGravityEnabled(true);
	}
	
}
