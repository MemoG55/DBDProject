// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/SurvivorGameplayAbility.h"
#include "GA_Survivor_DropItem.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Survivor_DropItem : public USurvivorGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_Survivor_DropItem();
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;
	
};
