// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GA/Interaction/GA_Survivor_PickUpItem.h"

#include "Shared/DBDGameplayTags.h"
#include "Shared/Component/InteractorComponent.h"


UGA_Survivor_PickUpItem::UGA_Survivor_PickUpItem()
{
	AbilityTags.AddTag(DBDGameplayTags::Survivor_Ability_Interaction_PickUpItem);
	ActivationRequiredTags.AddTag(DBDGameplayTags::Interactable_Object_SurvivorItem);
}

void UGA_Survivor_PickUpItem::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
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
		InteractStart();
		K2_EndAbility();
	}
}
