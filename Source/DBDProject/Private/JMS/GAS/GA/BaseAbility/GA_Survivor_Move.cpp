// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GA/BaseAbility/GA_Survivor_Move.h"

#include "Shared/DBDGameplayTags.h"


UGA_Survivor_Move::UGA_Survivor_Move()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(DBDGameplayTags::Survivor_Ability_Move);
	ActivationBlockedTags.AddTag(DBDGameplayTags::Survivor_Status_MoveDisabled);
	ActivationOwnedTags.AddTag(DBDGameplayTags::Survivor_Status_Moving);
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
}

void UGA_Survivor_Move::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	if (!IsActive())
	{
		K2_ActivateAbility();
	}
}

void UGA_Survivor_Move::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	if (IsActive())
	{
		K2_EndAbility();
	}
}
