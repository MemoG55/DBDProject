// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GA/UseItem/GA_UseFireCracker.h"

#include "JMS/Character/SurvivorCharacter.h"
#include "Shared/DBDGameplayTags.h"


UGA_UseFireCracker::UGA_UseFireCracker()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(DBDGameplayTags::Survivor_Ability_UseItem_UseFireCracker);
	ActivationRequiredTags.AddTag(DBDGameplayTags::Survivor_Item_FireCracker);
}

void UGA_UseFireCracker::InputPressed(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo,
                                      const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	if (!IsActive())
	{
		K2_ActivateAbility();
	}
}

void UGA_UseFireCracker::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (K2_HasAuthority())
	{
		GetSurvivorCharacterFromActorInfo()->UseEquippedItem();
		GetSurvivorCharacterFromActorInfo()->DropItem();
	}

	K2_EndAbility();
}
