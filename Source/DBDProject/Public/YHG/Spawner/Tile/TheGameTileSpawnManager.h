// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheGameTileSpawnManager.generated.h"

DECLARE_DELEGATE(FFinishedTileSpawnDelegate);

class ATheGameTileSpawner;
class ATheGameMidTileSpawner;
class ATheGameEdgeTileSpawner;
class ATheGameCornerTileSpawner;

UCLASS()
class DBDPROJECT_API ATheGameTileSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATheGameTileSpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditInstanceOnly, Category = "SpawnTile")
	TArray<ATheGameCornerTileSpawner*> CornerTileSpawners;

	UPROPERTY(EditInstanceOnly, Category = "SpawnTile")
	TArray<ATheGameEdgeTileSpawner*> EdgeTileSpawners;
	
	TMap<TArray<int32>, TArray<int32>> EscapeEdgeTileSpawnerIndexArrays;

	TArray<TArray<int32>> DoubleRoomEdgeTileIndexSelectArrays;
	
	UPROPERTY(EditInstanceOnly, Category = "SpawnTile")
	TArray<ATheGameMidTileSpawner*> MidTileSpawners;
	
public:
	void CornerTileSpawn();
	void EdgeTileSpawn();
	void MidTileSpawn();
	
	FFinishedTileSpawnDelegate OnFinishedTileSpawnDelegate;
};
