// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/GAS/GA_TestInteraction_Killer.h"

#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Component/InteractorComponent.h"


UGA_TestInteraction_Killer::UGA_TestInteraction_Killer()
{
	AbilityTags.AddTag(DBDGameplayTags::Killer_Common_Ability_Interaction_Test);
}

void UGA_TestInteraction_Killer::InputPressed(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	if (!IsActive())
	{
		K2_ActivateAbility();
	}
}

void UGA_TestInteraction_Killer::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	
}

void UGA_TestInteraction_Killer::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
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
		// TODO :: 캐비닛 -> 숨기 모션, 나가기 모션 중 어빌리티 종료 안되게 막기 (Hold 타입이 아닌 StartInteraction만 호출)
		CachedInteractorComponent->InteractWithCurrentInteractable();
	}
	if (!bIsHoldType)
	{
		K2_EndAbility();
	}
}

void UGA_TestInteraction_Killer::EndAbility(const FGameplayAbilitySpecHandle Handle,
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
		// TODO :: 캐비닛 -> 숨기 모션, 나가기 모션 중 어빌리티 종료 안되게 막기 (Hold 타입이 아닌 StartInteraction만 호출)
		InteractorComponent->EndInteraction();
	}
}
