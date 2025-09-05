// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/Spawner/Tile/EdgeTileSpawner.h"

TArray<TSubclassOf<AActor>> AEdgeTileSpawner::GetEscapeTileActors()
{
	return EscapeTileActors;
}

TArray<TSubclassOf<AActor>> AEdgeTileSpawner::GetDoubleRoomTileActors()
{
	return DoubleRoomTileActors;
}

void AEdgeTileSpawner::SpawnEscapeTile(int32 TargetTilesIndex)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	GetWorld()->SpawnActor<AActor>(EscapeTileActors[TargetTilesIndex], GetActorLocation(), GetActorRotation(),SpawnParameters);
}

void AEdgeTileSpawner::SpawnDoubleRoomTile(int32 TargetTilesIndex)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	GetWorld()->SpawnActor<AActor>(DoubleRoomTileActors[TargetTilesIndex], GetActorLocation(), GetActorRotation(),SpawnParameters);
}
