// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GA/Interaction/GA_SurvivorHealOther.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/Component/SkillCheckComponent.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/Component/InteractableComponent.h"
#include "Shared/Component/InteractorComponent.h"


UGA_SurvivorHealOther::UGA_SurvivorHealOther()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(DBDGameplayTags::Survivor_Ability_Interaction_HealOther);
	ActivationRequiredTags.AddTag(DBDGameplayTags::Interactable_Character_Survivor);
	ActivationOwnedTags.AddTag(DBDGameplayTags::Survivor_Status_MoveDisabled);
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
}

void UGA_SurvivorHealOther::InputPressed(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo,
                                               const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	if (!IsActive())
	{
		K2_ActivateAbility();
	}
}

void UGA_SurvivorHealOther::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
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
		ASurvivorCharacter* Generator = Cast<ASurvivorCharacter>(CachedInteractorComponent->GetCurrentInteractableActor());
		if (Generator)
		{
			CachedSurvivor = Generator;
			CachedSurvivor->GetInteractableComponent()->OnComplete.AddDynamic(
				this, &UGA_SurvivorHealOther::K2_EndAbility);
		}
	}
	else
	{
		K2_EndAbility();
	}

	CachedSkillCheckComponent = GetSkillCheckComponentFromActorInfo();
	if (CachedSkillCheckComponent)
	{
		CachedSkillCheckComponent->SkillCheckEndDelegate.AddDynamic(
			this, &UGA_SurvivorHealOther::OnSkillCheckEnd);
	}

	// PredictionKey는 클라이언트가 서버의 명령 없이 예측해서 실행할 때 사용 - 애니메이션 재생 등 중요한 로직이 아닐 경우
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		ASC->PlayMontage(this, ActivationInfo, HealMontage, 1.f);
		GetSurvivorCharacterFromActorInfo()->MoveEnabled(false);
	}
	if (IsLocallyControlled())
	{
		SetSkillCheckTimer(1.0f);
	}
}

void UGA_SurvivorHealOther::InputReleased(const FGameplayAbilitySpecHandle Handle,
                                                const FGameplayAbilityActorInfo* ActorInfo,
                                                const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	if (IsActive())
	{
		K2_EndAbility();
	}
}

void UGA_SurvivorHealOther::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo,
                                             const FGameplayAbilityActivationInfo ActivationInfo,
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
	if (CachedSkillCheckComponent)
	{
		CachedSkillCheckComponent->SkillCheckEndDelegate.RemoveDynamic(
			this, &UGA_SurvivorHealOther::OnSkillCheckEnd);
		CachedSkillCheckComponent->OnEndSkillCheck();
	}
	if (CachedSurvivor)
	{
		CachedSurvivor->GetInteractableComponent()->OnComplete.RemoveDynamic(
			this, &UGA_SurvivorHealOther::K2_EndAbility);
	}
	GetWorld()->GetTimerManager().ClearTimer(SkillCheckTimerHandle);
	GetSurvivorCharacterFromActorInfo()->MoveEnabled(true);
}

void UGA_SurvivorHealOther::OnSkillCheckEnd(ESkillCheckResult Result)
{
	Server_SendSkillCheckResult(Result);
	SetSkillCheckTimer(1.f);
}

void UGA_SurvivorHealOther::Server_SendSkillCheckResult_Implementation(ESkillCheckResult Result)
{
	FGameplayEventData EventData;
	EventData.EventTag = DBDGameplayTags::Object_Event_Result_Failure;
	EventData.Instigator = GetAvatarActorFromActorInfo();

	switch (Result)
	{
	case ESkillCheckResult::Bad:
		EventData.InstigatorTags = FGameplayTagContainer(DBDGameplayTags::Object_Event_Result_Failure);
		break;
	case ESkillCheckResult::Great:
		EventData.InstigatorTags = FGameplayTagContainer(DBDGameplayTags::Object_Event_Result_Success);
		break;
	default:
		break;
	}
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(CachedSurvivor, DBDGameplayTags::Object_Event_Check,
	                                                         EventData);
}

void UGA_SurvivorHealOther::SetSkillCheckTimer(float frequency)
{
	if (frequency <= 0)
	{
		Debug::Print(TEXT("JMS17: SetSkillCheckTimer : frequency should be larger than 0"), 17);
		return;
	}
	// 임시로 10~15초 사이에 스킬 체크 발생
	GetWorld()->GetTimerManager().SetTimer(SkillCheckTimerHandle, this, &UGA_SurvivorHealOther::PlaySkillCheck,
	                                       FMath::RandRange(5.f / frequency, 10.f / frequency), false);
}

void UGA_SurvivorHealOther::PlaySkillCheck()
{
	if (CachedSkillCheckComponent)
	{
		CachedSkillCheckComponent->TriggerOneShotSkillCheck(3.f, FMath::RandRange(1.0f, 1.7f), 1.f, .5f);
	}
}

void UGA_SurvivorHealOther::OnSkillCheckInterrupted()
{
}

