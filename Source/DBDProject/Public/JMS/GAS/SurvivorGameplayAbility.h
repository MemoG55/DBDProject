// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/GAS/GA/DBDGameplayAbility.h"
#include "SurvivorGameplayAbility.generated.h"

class UInteractableComponent;
class ASurvivorCharacter;
class USkillCheckComponent;
class USurvivorAbilitySystemComponent;
class UInteractorComponent;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API USurvivorGameplayAbility : public UDBDGameplayAbility
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintPure, Category="GA")
	UInteractableComponent* GetInteractableComponentFromActorInfo() const;
	
	UFUNCTION(BlueprintPure, Category="GA")
	USkillCheckComponent* GetSkillCheckComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category="GA")
	USurvivorAbilitySystemComponent* GetSurvivorAbilitySystemComponentFromActorInfo() const;
	UFUNCTION(BlueprintPure, Category="GA")
	UAnimInstance* GetAnimInstance() const;

	ASurvivorCharacter* GetSurvivorCharacterFromActorInfo() const;
	
};
