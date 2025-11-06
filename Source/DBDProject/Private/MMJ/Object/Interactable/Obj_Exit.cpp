// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Interactable/Obj_Exit.h"

#include "MMJ/Object/Component/IC_Exit.h"
#include "MMJ/Object/Spawner/EntitySpawner.h"
#include "MMJ/Object/Subsystem/EntitySpawnSubsystem.h"

AObj_Exit::AObj_Exit(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UIC_Exit>(ADBDObject::InteractableComponentName))
{
}

void AObj_Exit::SpawnEntity()
{
	if (UEntitySpawnSubsystem* EntitySpawnSubsystem = GetWorld()->GetSubsystem<UEntitySpawnSubsystem>())
	{
		if (AEntitySpawner* EntitySpawner = EntitySpawnSubsystem->GetEntitySpawner())
		{
			Entity = EntitySpawner->SpawnEntity(this, GetInteractableComponent()->InteractableTag);
		}
	}
}

void AObj_Exit::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		FTimerHandle  TimerHandle;
		GetWorldTimerManager().SetTimer(
			TimerHandle,
			FTimerDelegate::CreateLambda([&]()
			{
				SpawnEntity();
			}),
			1.f,
			false);
			
	}
}
