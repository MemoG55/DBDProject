// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GA/Passive/GA_Survivor_Dying.h"

#include "Shared/DBDGameplayTags.h"


UGA_Survivor_Dying::UGA_Survivor_Dying()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(DBDGameplayTags::Survivor_Ability_Passive_Dying);
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::OwnedTagPresent;
	TriggerData.TriggerTag = DBDGameplayTags::Survivor_Status_Dying;
	AbilityTriggers.Add(TriggerData);
}

void UGA_Survivor_Dying::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (K2_HasAuthority())
	{
		DyingEffectHandle = BP_ApplyGameplayEffectToOwner(ChangeSpeedOnDyingEffect);
	}
}

void UGA_Survivor_Dying::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                                    bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if (K2_HasAuthority() && DyingEffectHandle.IsValid())
	{
		BP_RemoveGameplayEffectFromOwnerWithHandle(DyingEffectHandle);
	}
}
