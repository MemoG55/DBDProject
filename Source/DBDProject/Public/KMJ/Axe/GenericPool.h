// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolableActor.h"
#include "ProjectileAxe.h"
#include "GameFramework/Actor.h"
#include "GenericPool.generated.h"

class APoolableActor;

UCLASS()
class DBDPROJECT_API AGenericPool : public AActor
{
	GENERATED_BODY()
public:
	AGenericPool();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Pool")
	TArray<AProjectileAxe*> ObjectPool;
	
	int32 idx = 0;

	template <typename T>
	void InitPool(UClass* ProjectileClass, int32 Size)
	{
		if (!ProjectileClass) return;

		for (int32 i = 0; i < Size; ++i) 
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			// BP 클래스로 스폰
			AProjectileAxe* NewActor = GetWorld()->SpawnActor<AProjectileAxe>(ProjectileClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
			NewActor->Deactivate();
			ObjectPool.Add(NewActor);
		}
	}


	template <typename T>
	T* GetObject(UClass* ObjectClass)
	{
		if (!ObjectClass || ObjectPool.Num() == 0) return nullptr;

		for (AProjectileAxe* Object : ObjectPool)
		{
			if (Object && !Cast<T>(Object)->GetIsActive() && Object->IsA(ObjectClass))
			{
				return Cast<T>(Object);
			}
		}

		// 순환 방식으로 반환
		AProjectileAxe* NewObject = ObjectPool[idx];
		if (NewObject)
		{
			Cast<T>(NewObject)->Deactivate();
			idx = (idx + 1) % ObjectPool.Num();
		}

		return Cast<T>(NewObject);
	}

	template <typename T>
	void ReturnObject(T* Object) {
		Object->Deactivate();
	}
};
