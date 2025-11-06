// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_PreloadAssets.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDA_PreloadAssets : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = PrimaryAssetLabel, meta = (AssetBundles = "Explicit"))
	TArray<TSoftObjectPtr<UObject>> AssetsToPreload;
	
	
	
	
};
