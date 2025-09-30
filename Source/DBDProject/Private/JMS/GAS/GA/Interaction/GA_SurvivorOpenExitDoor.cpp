// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GA/Interaction/GA_SurvivorOpenExitDoor.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "MMJ/Object/Interactable/Obj_ExitDoor.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Component/InteractableComponent.h"
#include "Shared/Component/InteractorComponent.h"


UGA_SurvivorOpenExitDoor::UGA_SurvivorOpenExitDoor()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(DBDGameplayTags::Survivor_Ability_Interaction_OpenExitDoor);
	ActivationOwnedTags.AddTag(DBDGameplayTags::Survivor_Status_MoveDisabled);

}

void UGA_SurvivorOpenExitDoor::InputPressed(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	if (!IsActive())
	{
		K2_ActivateAbility();
	}
}

void UGA_SurvivorOpenExitDoor::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
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
	CachedInteractorComponent = GetInteractorComponentFromActorInfo();
	if (CachedInteractorComponent)
	{
		CachedInteractorComponent->InteractWithCurrentInteractable();
	}
	if (CachedInteractorComponent->GetCurrentInteractableActor())
	{
		AObj_ExitDoor* ExitDoor = Cast<AObj_ExitDoor>(CachedInteractorComponent->GetCurrentInteractableActor());
		if (ExitDoor)
		{
			CachedExitDoor = ExitDoor;
			CachedExitDoor->GetInteractableComponent()->OnComplete.AddDynamic(
				this, &UGA_SurvivorOpenExitDoor::K2_EndAbility);
		}
	}

	// PredictionKey는 클라이언트가 서버의 명령 없이 예측해서 실행할 때 사용 - 애니메이션 재생 등 중요한 로직이 아닐 경우
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		UAbilityTask_PlayMontageAndWait* PlayStartMontageTask =
			UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
				this, NAME_None, StartMontage, 1.f);
		PlayStartMontageTask->OnBlendOut.AddDynamic(this, &UGA_SurvivorOpenExitDoor::PlayLoopMontage);
		PlayStartMontageTask->OnCancelled.AddDynamic(this, &UGA_SurvivorOpenExitDoor::PlayLoopMontage);
		PlayStartMontageTask->OnCompleted.AddDynamic(this, &UGA_SurvivorOpenExitDoor::PlayLoopMontage);
		PlayStartMontageTask->OnInterrupted.AddDynamic(this, &UGA_SurvivorOpenExitDoor::PlayLoopMontage);
		PlayStartMontageTask->ReadyForActivation();
		GetSurvivorCharacterFromActorInfo()->MoveEnabled(false);
	}
}

void UGA_SurvivorOpenExitDoor::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	if (IsActive())
	{
		K2_EndAbility();
	}
}

void UGA_SurvivorOpenExitDoor::PlayLoopMontage()
{
	if (IsActive())
	{
		UAbilityTask_PlayMontageAndWait* PlayLoopMontageTask =
			UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
				this, NAME_None, LoopMontage, 1.f);
		PlayLoopMontageTask->OnBlendOut.AddDynamic(this, &UGA_SurvivorOpenExitDoor::K2_EndAbility);
		PlayLoopMontageTask->OnCancelled.AddDynamic(this, &UGA_SurvivorOpenExitDoor::K2_EndAbility);
		PlayLoopMontageTask->OnCompleted.AddDynamic(this, &UGA_SurvivorOpenExitDoor::K2_EndAbility);
		PlayLoopMontageTask->OnInterrupted.AddDynamic(this, &UGA_SurvivorOpenExitDoor::K2_EndAbility);
		PlayLoopMontageTask->ReadyForActivation();
	}
	else
	{
		K2_EndAbility();
	}
}

void UGA_SurvivorOpenExitDoor::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if (GetAnimInstance())
	{
		GetAnimInstance()->StopAllMontages(0.1f);
	}
	UInteractorComponent* InteractorComponent = GetInteractorComponentFromActorInfo();
	if (InteractorComponent)
	{
		InteractorComponent->EndInteraction();
	}
	if (CachedExitDoor)
	{
		CachedExitDoor->GetInteractableComponent()->OnComplete.RemoveDynamic(
			this, &UGA_SurvivorOpenExitDoor::K2_EndAbility);
	}
	GetSurvivorCharacterFromActorInfo()->MoveEnabled(true);
}
