// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/Spawner/Tile/TheGameTileSpawner.h"

#include "YHG/Tile/TheGameTile.h"

// Sets default values
ATheGameTileSpawner::ATheGameTileSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATheGameTileSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATheGameTileSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<TSubclassOf<ATheGameTile>> ATheGameTileSpawner::GetTileActors()
{
	return TileActors;
}


void ATheGameTileSpawner::SpawnTile(const int32 TargetTilesIndex)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	GetWorld()->SpawnActor<ATheGameTile>(TileActors[TargetTilesIndex], GetActorLocation(), GetActorRotation(),SpawnParameters);
}

