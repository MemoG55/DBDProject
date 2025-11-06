// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/AbilityPriorityInterface.h"
#include "JMS/GAS/SurvivorGameplayAbility.h"
#include "SurvivorNoiseAbility.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API USurvivorNoiseAbility : public USurvivorGameplayAbility, public IAbilityPriorityInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetPriority() const override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Ability Priority")
	int32 Priority = 0;
};
