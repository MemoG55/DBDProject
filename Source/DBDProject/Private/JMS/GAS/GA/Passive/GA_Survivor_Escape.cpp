// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GA/Passive/GA_Survivor_Escape.h"

#include "JMS/Character/SurvivorCharacter.h"
#include "Shared/DBDGameplayTags.h"


UGA_Survivor_Escape::UGA_Survivor_Escape()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	AbilityTags.AddTag(DBDGameplayTags::Survivor_Ability_Passive_Escape);
	ActivationOwnedTags.AddTag(DBDGameplayTags::Survivor_Status_MoveDisabled);
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::OwnedTagPresent;
	TriggerData.TriggerTag = DBDGameplayTags::Survivor_Status_Escaped;
	AbilityTriggers.Add(TriggerData);
}

void UGA_Survivor_Escape::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	GetSurvivorCharacterFromActorInfo()->SetCollisionAndGravityEnabled(false);
	GetSurvivorCharacterFromActorInfo()->SetActorHiddenInGame(true);
}
