// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "DBDDataBase.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDBDDataBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UDataTable> SurvivorPerkDB;
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UDataTable> KillerPerkDB;
};
