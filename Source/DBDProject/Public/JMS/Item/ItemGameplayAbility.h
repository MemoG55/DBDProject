// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/GAS/GA/DBDGameplayAbility.h"
#include "ItemGameplayAbility.generated.h"

class UItemAbilitySystemComponent;
class UInteractorComponent;
class ASurvivorCharacter;
class USurvivorAbilitySystemComponent;
class USkillCheckComponent;
class UInteractableComponent;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UItemGameplayAbility : public UDBDGameplayAbility
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintPure, Category="GA")
	UInteractableComponent* GetOwnerInteractableComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category="GA")
	UInteractorComponent* GetOwnerInteractorComponentFromActorInfo() const;	
	
	UFUNCTION(BlueprintPure, Category="GA")
	USkillCheckComponent* GetOwnerSkillCheckComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category="GA")
	USurvivorAbilitySystemComponent* GetOwnerSurvivorAbilitySystemComponentFromActorInfo() const;
	
	UFUNCTION(BlueprintPure, Category="GA")
	UAnimInstance* GetOwnerAnimInstance() const;

	UFUNCTION(BlueprintPure, Category="GA")
	ASurvivorCharacter* GetOwnerSurvivorCharacterFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category="GA")
	UItemAbilitySystemComponent* GetItemAbilitySystemComponentFromActorInfo() const;
};
