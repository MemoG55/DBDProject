// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/SurvivorGameplayAbility.h"
#include "GA_Survivor_Move.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Survivor_Move : public USurvivorGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_Survivor_Move();
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	
	
	
	
};
