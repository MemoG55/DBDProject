// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/GA/SurvivorUseItemAbility.h"
#include "JMS/GAS/SurvivorGameplayAbility.h"
#include "GA_UseFireCracker.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_UseFireCracker : public USurvivorUseItemAbility
{
	GENERATED_BODY()

public:
	UGA_UseFireCracker();
public:
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	
};
