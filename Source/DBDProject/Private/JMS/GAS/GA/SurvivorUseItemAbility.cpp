// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GA/SurvivorUseItemAbility.h"

#include "Shared/DBDGameplayTags.h"


USurvivorUseItemAbility::USurvivorUseItemAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ActivationBlockedTags.AddTag(DBDGameplayTags::Survivor_Status_Captured);
	ActivationBlockedTags.AddTag(DBDGameplayTags::Survivor_Status_Dying);
	ActivationBlockedTags.AddTag(DBDGameplayTags::Survivor_Status_Dead);
	ActivationBlockedTags.AddTag(DBDGameplayTags::Survivor_Status_Escaped);
	ActivationBlockedTags.AddTag(DBDGameplayTags::Survivor_Status_Hooked);
}
