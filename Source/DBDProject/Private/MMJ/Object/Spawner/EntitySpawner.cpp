// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Spawner/EntitySpawner.h"

#include "MMJ/Object/Interactable/Obj_Entity.h"
#include "MMJ/Object/Subsystem/EntitySpawnSubsystem.h"

// Sets default values
AEntitySpawner::AEntitySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

AObj_Entity* AEntitySpawner::SpawnEntity(ADBDObject* OwnerObject, FGameplayTag EntityTag)
{
	if (!OwnerObject) return nullptr;
	if (TSubclassOf<AObj_Entity> EntityClass = GetEntityInfo(EntityTag))
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = OwnerObject;
		if (AObj_Entity* Entity = GetWorld()->SpawnActor<AObj_Entity>(EntityClass, SpawnParameters))
		{
			Entity->AttachToActor(OwnerObject, FAttachmentTransformRules::KeepRelativeTransform);
			return Entity;
		}
	}

	return nullptr;
}

// Called when the game starts or when spawned
void AEntitySpawner::BeginPlay()
{
	Super::BeginPlay();

	if (UEntitySpawnSubsystem* EntitySpawnSubsystem = GetWorld()->GetSubsystem<UEntitySpawnSubsystem>())
	{
		EntitySpawnSubsystem->SetEntitySpawner(this);
	}
}

TSubclassOf<AObj_Entity> AEntitySpawner::GetEntityInfo(FGameplayTag EntityTag)
{
	for (const FEntitySpawnInfo& EntityInfo : EntityInfos)
	{
		if (EntityInfo.EntityTag == EntityTag)
		{
			return EntityInfo.EntityClass;
		}
	}

	return nullptr;
}

