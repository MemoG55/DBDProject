// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/Spawner/Tile/TheGameEdgeTileSpawner.h"

#include "YHG/Tile/TheGameTile.h"

void ATheGameEdgeTileSpawner::BeginPlay()
{
	Super::BeginPlay();
}

TArray<TSubclassOf<ATheGameTile>> ATheGameEdgeTileSpawner::GetEscapeTileActors()
{
	return EscapeTileActors;
}
/*
TArray<TSubclassOf<ATheGameTile>> ATheGameEdgeTileSpawner::GetDoubleRoomTileActors()
{
	return DoubleRoomTileActors;
}*/

void ATheGameEdgeTileSpawner::SpawnEscapeTile(int32 TargetTilesIndex)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	GetWorld()->SpawnActor<ATheGameTile>(EscapeTileActors[TargetTilesIndex], GetActorLocation(), GetActorRotation(),SpawnParameters);
}
/*
void ATheGameEdgeTileSpawner::SpawnDoubleRoomTile(int32 TargetTilesIndex)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	GetWorld()->SpawnActor<ATheGameTile>(DoubleRoomTileActors[TargetTilesIndex], GetActorLocation(), GetActorRotation(),SpawnParameters);
}*/
