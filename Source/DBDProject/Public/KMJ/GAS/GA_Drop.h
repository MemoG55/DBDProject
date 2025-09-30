// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KMJ/GAS/KillerGameplayAbility.h"
#include "GA_Drop.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Drop : public UKillerGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetSurvivorGAClearAndDetach(AActor* Killer);
};
