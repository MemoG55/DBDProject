// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Engine/DataAsset.h"
#include "ObjDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UObjDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, Category = "GEs")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;

	UPROPERTY(EditDefaultsOnly, Category = "GE")
	TSubclassOf<UGameplayEffect> ActiveEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "GE")
	TSubclassOf<UGameplayEffect> DestroyEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "GA")
	TArray<TSubclassOf<UGameplayAbility>> InitializedAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "GA")
	TSubclassOf<UGameplayAbility> ActiveAbility;

	UPROPERTY(EditDefaultsOnly, Category = "GA")
	TSubclassOf<UGameplayAbility> DestroyAbility;
};
