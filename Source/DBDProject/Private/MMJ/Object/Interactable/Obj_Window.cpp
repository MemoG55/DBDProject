// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Interactable/Obj_Window.h"

#include "MMJ/Object/Spawner/EntitySpawner.h"
#include "MMJ/Object/Subsystem/EntitySpawnSubsystem.h"
#include "Shared/Component/InteractableComponent.h"

AObj_Window::AObj_Window(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	ObjectStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("ObjectStaticMesh");
	ObjectStaticMesh->SetupAttachment(ObjectMesh);
}

void AObj_Window::SpawnEntity()
{
	if (UEntitySpawnSubsystem* EntitySpawnSubsystem = GetWorld()->GetSubsystem<UEntitySpawnSubsystem>())
	{
		if (AEntitySpawner* EntitySpawner = EntitySpawnSubsystem->GetEntitySpawner())
		{
			Entity = EntitySpawner->SpawnEntity(this, GetInteractableComponent()->InteractableTag);
		}
	}
}