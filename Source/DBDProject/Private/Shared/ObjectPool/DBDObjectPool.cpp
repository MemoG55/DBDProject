// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/ObjectPool/DBDObjectPool.h"

#include "Shared/ObjectPool/DBDPoolEntryObject.h"


// Sets default values
ADBDObjectPool::ADBDObjectPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

ADBDPoolEntryObject* ADBDObjectPool::SpawnPooledObject(APawn* InInstigator)
{
	for (ADBDPoolEntryObject* PoolableActor : ObjectPool)
	{
		if (PoolableActor != nullptr && !PoolableActor->IsActive())
		{
			PoolableActor->TeleportTo(FVector::ZeroVector, FRotator::ZeroRotator);
			PoolableActor->SetLifeTime(PooledObjectLifeTime);
			PoolableActor->SetActive(true, InInstigator);
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());
			return PoolableActor;
		}
	}

	if (SpawnedPoolIndexes.Num() > 0)
	{
		int PooledObjectIndex = SpawnedPoolIndexes[0];
		SpawnedPoolIndexes.Remove(PooledObjectIndex);
		ADBDPoolEntryObject* PoolableActor = ObjectPool[PooledObjectIndex];
		if (PoolableActor != nullptr)
		{
			PoolableActor->TeleportTo(FVector::ZeroVector, FRotator::ZeroRotator);
			PoolableActor->SetLifeTime(PooledObjectLifeTime);
			PoolableActor->SetActive(true, InInstigator);
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());
			return PoolableActor;
		}
	}

	return nullptr;
}

void ADBDObjectPool::OnPooledObjectDespawn(ADBDPoolEntryObject* PoolActor)
{
	SpawnedPoolIndexes.Remove(PoolActor->GetPoolIndex());
}

void ADBDObjectPool::DeactivateAllPooledObjects()
{
	while (SpawnedPoolIndexes.Num() > 0)
	{
		ObjectPool[SpawnedPoolIndexes[0]]->Deactivate();
	}
}

// Called when the game starts or when spawned
void ADBDObjectPool::BeginPlay()
{
	Super::BeginPlay();
	if (PooledObjectClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			for (int i = 0; i < PoolSize; i++)
			{
				ADBDPoolEntryObject* PoolableActor = World->SpawnActor<ADBDPoolEntryObject>(
					PooledObjectClass, FVector::ZeroVector, FRotator::ZeroRotator);
				if (PoolableActor != nullptr)
				{
					PoolableActor->SetActive(false, nullptr);
					PoolableActor->SetPoolIndex(i);
					PoolableActor->OnPooledObjectDespawn.AddDynamic(this, &ADBDObjectPool::OnPooledObjectDespawn);
					ObjectPool.Add(PoolableActor);
				}
			}
		}
	}
}


