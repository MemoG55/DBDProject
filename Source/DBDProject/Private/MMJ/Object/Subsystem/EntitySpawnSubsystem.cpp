// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Subsystem/EntitySpawnSubsystem.h"

AEntitySpawner* UEntitySpawnSubsystem::GetEntitySpawner() const
{
	return EntitySpawner;
}

void UEntitySpawnSubsystem::SetEntitySpawner(AEntitySpawner* Spawner)
{
	if (!Spawner) return;
	EntitySpawner = Spawner;
}
