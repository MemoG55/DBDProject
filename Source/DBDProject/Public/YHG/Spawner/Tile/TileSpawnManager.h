// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileSpawnManager.generated.h"

class AMidTileSpawner;
class AEdgeTileSpawner;
class ACornerTileSpawner;

UCLASS()
class DBDPROJECT_API ATileSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileSpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditInstanceOnly, Category = "SpawnTile")
	TArray<ACornerTileSpawner*> CornerTileSpawners;

	UPROPERTY(EditInstanceOnly, Category = "SpawnTile")
	TArray<AEdgeTileSpawner*> EdgeTileSpawners;
	
	TMap<TArray<int32>, TArray<int32>> EscapeEdgeTileSpawnerIndexArrays;

	TArray<TArray<int32>> DoubleRoomEdgeTileIndexSelectArrays;
	
	UPROPERTY(EditInstanceOnly, Category = "SpawnTile")
	TArray<AMidTileSpawner*> MidTileSpawners;
	
public:
	void CornerTileSpawn();
	void EdgeTileSpawn();
	void MidTileSpawn();
};
