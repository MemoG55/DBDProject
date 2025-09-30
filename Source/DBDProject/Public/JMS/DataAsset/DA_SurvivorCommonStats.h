// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_SurvivorCommonStats.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDA_SurvivorCommonStats : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float MaxHookHP;
	UPROPERTY(EditAnywhere)
	float MaxDyingHP;
	UPROPERTY(EditAnywhere)
	float MaxHealProgress;
	UPROPERTY(EditAnywhere)
	float MovementSpeed;
	UPROPERTY(EditAnywhere)
	float GeneratorRepairSpeed;
	UPROPERTY(EditAnywhere)
	float HealSpeed;
	UPROPERTY(EditAnywhere)
	float SkillCheckFrequency;
};
