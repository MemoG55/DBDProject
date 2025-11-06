// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "DBDAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDBDAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UDBDAssetManager& Get();

	virtual void StartInitialLoading() override;

	void StartAsyncLoading(const TArray<FSoftObjectPath>& AssetsToLoad);
	void StartStaticMeshLoading();
	
};
