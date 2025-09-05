// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YHG/Spawner/Tile/TileSpawner.h"
#include "EdgeTileSpawner.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API AEdgeTileSpawner : public ATileSpawner
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "TileActors")
	TArray<TSubclassOf<AActor>> EscapeTileActors;
	UPROPERTY(EditDefaultsOnly, Category = "TileActors")
	TArray<TSubclassOf<AActor>> DoubleRoomTileActors;

public:
	TArray<TSubclassOf<AActor>> GetEscapeTileActors();
	TArray<TSubclassOf<AActor>> GetDoubleRoomTileActors();

	void SpawnEscapeTile(int32 TargetTilesIndex);
	void SpawnDoubleRoomTile(int32 TargetTilesIndex);
};
