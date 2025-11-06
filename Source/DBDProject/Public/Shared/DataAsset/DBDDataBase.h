// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DBDDataBase.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDBDDataBase : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "PerkDB")
	TSoftObjectPtr<UDataTable> SurvivorPerkDB;
	UPROPERTY(EditDefaultsOnly, Category = "PerkDB")
	TSoftObjectPtr<UDataTable> KillerPerkDB;
	
	UPROPERTY(EditDefaultsOnly, Category = "SurvivorItemDB")
	TSoftObjectPtr<UDataTable> SurvivorItemDB;
	UPROPERTY(EditDefaultsOnly, Category = "SurvivorItemDB")
	TSoftObjectPtr<UDataTable> ItemAddonDB;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterDB")
	TSoftObjectPtr<UDataTable> SurvivorCharacterDB;
};
