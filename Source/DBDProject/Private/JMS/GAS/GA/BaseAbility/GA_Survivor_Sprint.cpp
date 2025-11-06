// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GA/BaseAbility/GA_Survivor_Sprint.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "Shared/DBDGameplayTags.h"


UGA_Survivor_Sprint::UGA_Survivor_Sprint()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(DBDGameplayTags::Survivor_Ability_Passive_Sprint);
	ActivationRequiredTags.AddTag(DBDGameplayTags::Survivor_Status_SprintEnabled);
	ActivationRequiredTags.AddTag(DBDGameplayTags::Survivor_Status_Moving);
	ActivationOwnedTags.AddTag(DBDGameplayTags::Survivor_Status_Sprinting);
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;

}

void UGA_Survivor_Sprint::InputPressed(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	if (!IsActive())
	{
		K2_ActivateAbility();
	}
}

void UGA_Survivor_Sprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		GetSurvivorCharacterFromActorInfo()->OnSprintStarted();
	}
}

void UGA_Survivor_Sprint::InputReleased(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo,
                                       const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	if (IsActive())
	{
		K2_EndAbility();
	}
}
