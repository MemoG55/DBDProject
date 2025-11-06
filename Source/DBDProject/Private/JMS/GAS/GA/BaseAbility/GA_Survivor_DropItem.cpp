// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GA/BaseAbility/GA_Survivor_DropItem.h"

#include "JMS/Character/SurvivorCharacter.h"
#include "Shared/DBDGameplayTags.h"


UGA_Survivor_DropItem::UGA_Survivor_DropItem()
{
	AbilityTags.AddTag(DBDGameplayTags::Survivor_Ability_DropItem);
}

void UGA_Survivor_DropItem::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
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
	if (K2_HasAuthority())
	{
		ASurvivorCharacter* OwnerSurvivorCharacter = GetSurvivorCharacterFromActorInfo();
		if (OwnerSurvivorCharacter)
		{
			OwnerSurvivorCharacter->DropItem(nullptr);
		}
	}
	K2_EndAbility();
}
