// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/SurvivorGameplayAbility.h"
#include "SurvivorUseItemAbility.generated.h"

class UItemAbilitySystemComponent;
class ASurvivorItem;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API USurvivorUseItemAbility : public USurvivorGameplayAbility
{
	GENERATED_BODY()
	
public:
	USurvivorUseItemAbility();
protected:
	UItemAbilitySystemComponent* GetItemAbilitySystemComponentFromActorInfo() const;
protected:
	UFUNCTION(BlueprintPure, Category="GA")
	UInteractorComponent* GetInteractorComponentFromActorInfo() const;	
	
};
