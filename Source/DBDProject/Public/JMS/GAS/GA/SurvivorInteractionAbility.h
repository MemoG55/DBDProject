// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/SurvivorGameplayAbility.h"
#include "SurvivorInteractionAbility.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API USurvivorInteractionAbility : public USurvivorGameplayAbility
{
	GENERATED_BODY()
public:
	USurvivorInteractionAbility();
protected:
	UFUNCTION(BlueprintPure, Category="GA")
	UInteractorComponent* GetInteractorComponentFromActorInfo() const;	
	
};
