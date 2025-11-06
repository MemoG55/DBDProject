// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Interactable/Obj_Chest.h"

#include "MMJ/Object/Component/IC_Chest.h"
#include "MMJ/Object/Spawner/EntitySpawner.h"
#include "MMJ/Object/Subsystem/EntitySpawnSubsystem.h"

AObj_Chest::AObj_Chest(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UIC_Chest>(InteractableComponentName))
{
}

void AObj_Chest::SpawnEntity()
{
	if (UEntitySpawnSubsystem* EntitySpawnSubsystem = GetWorld()->GetSubsystem<UEntitySpawnSubsystem>())
	{
		if (AEntitySpawner* EntitySpawner = EntitySpawnSubsystem->GetEntitySpawner())
		{
			Entity = EntitySpawner->SpawnEntity(this, GetInteractableComponent()->InteractableTag);
		}
	}
}

void AObj_Chest::BeginPlay()
{
	Super::BeginPlay();

	SpawnEntity();
}
