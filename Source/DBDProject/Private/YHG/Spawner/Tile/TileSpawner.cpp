// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/Spawner/Tile/TileSpawner.h"

// Sets default values
ATileSpawner::ATileSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATileSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATileSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<TSubclassOf<AActor>> ATileSpawner::GetTileActors()
{
	return TileActors;
}

void ATileSpawner::SpawnTile(int32 TargetTilesIndex)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	GetWorld()->SpawnActor<AActor>(TileActors[TargetTilesIndex], GetActorLocation(), GetActorRotation(),SpawnParameters);
}

