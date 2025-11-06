// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/GAS/GA/DBDGameplayAbility.h"
#include "KillerGameplayAbility.generated.h"

class UInteractorComponent;
class UKillerAbilitySystemComponent;
class UAnimInstance;
class AKillerCharacter;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UKillerGameplayAbility : public UDBDGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category="GA")
	UInteractorComponent* GetInteractorComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category="GA")
	UKillerAbilitySystemComponent* GetKillerAbilitySystemComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category="GA")
	UAnimInstance* GetAnimInstance() const;

	UFUNCTION(BlueprintPure, Category="GA")
	AKillerCharacter* GetKillerCharacterFromActorInfo() const;

	UPROPERTY(BlueprintReadOnly)
	AKillerCharacter* Killer;
};
