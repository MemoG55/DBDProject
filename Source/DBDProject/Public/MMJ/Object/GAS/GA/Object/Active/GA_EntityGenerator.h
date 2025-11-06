// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/GAS/GA/Object/Active/GA_Active.h"
#include "GA_EntityGenerator.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_EntityGenerator : public UGA_Active
{
	GENERATED_BODY()
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	
};
