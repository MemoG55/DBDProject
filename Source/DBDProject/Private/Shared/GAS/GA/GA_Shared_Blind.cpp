// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/GAS/GA/GA_Shared_Blind.h"

#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDGameplayTags.h"


UGA_Shared_Blind::UGA_Shared_Blind()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(DBDGameplayTags::Shared_Ability_Blind);
	
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::OwnedTagPresent;
	TriggerData.TriggerTag = DBDGameplayTags::Shared_Status_Blind;
	AbilityTriggers.Add(TriggerData);
}

void UGA_Shared_Blind::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo,
                                       const FGameplayAbilityActivationInfo ActivationInfo,
                                       const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (K2_HasAuthority())
	{
		//Debug::Print(TEXT("JMS13: Blind Activated"), 13);
	}
}
