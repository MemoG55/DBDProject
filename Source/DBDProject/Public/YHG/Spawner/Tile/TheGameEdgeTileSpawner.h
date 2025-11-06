// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YHG/Spawner/Tile/TheGameTileSpawner.h"
#include "TheGameEdgeTileSpawner.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API ATheGameEdgeTileSpawner : public ATheGameTileSpawner
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "TileActors")
	TArray<TSubclassOf<ATheGameTile>> EscapeTileActors;
	//UPROPERTY(EditDefaultsOnly, Category = "TileActors")
	//TArray<TSubclassOf<ATheGameTile>> DoubleRoomTileActors;
public:
	TArray<TSubclassOf<ATheGameTile>> GetEscapeTileActors();
	//TArray<TSubclassOf<ATheGameTile>> GetDoubleRoomTileActors();

	void SpawnEscapeTile(int32 TargetTilesIndex);
	// SpawnDoubleRoomTile(int32 TargetTilesIndex);
};
