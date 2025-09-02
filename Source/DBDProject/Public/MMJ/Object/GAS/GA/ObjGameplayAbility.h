// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/GAS/DBDAbilitySystemComponent.h"
#include "Shared/GAS/GA/DBDGameplayAbility.h"
#include "ObjGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UObjGameplayAbility : public UDBDGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "GA")
	UDBDAbilitySystemComponent* GetMGAbilitySystemComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "GA")
	UAnimInstance* GetAnimInstance() const;

protected:
	UPROPERTY()
	FTimerHandle TaskTimerHandle;
};
