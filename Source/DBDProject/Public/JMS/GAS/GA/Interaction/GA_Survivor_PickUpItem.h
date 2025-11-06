// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/GA/SurvivorInteractionAbility.h"
#include "GA_Survivor_PickUpItem.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Survivor_PickUpItem : public USurvivorInteractionAbility
{
	GENERATED_BODY()
public:
	UGA_Survivor_PickUpItem();
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;
	
	
};
