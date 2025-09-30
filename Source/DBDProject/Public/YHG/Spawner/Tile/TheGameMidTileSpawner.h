// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YHG/Spawner/Tile/TheGameTileSpawner.h"
#include "TheGameMidTileSpawner.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API ATheGameMidTileSpawner : public ATheGameTileSpawner
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
};
