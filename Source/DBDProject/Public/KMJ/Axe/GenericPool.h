// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolableActor.h"
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

private:
	UPROPERTY(EditAnywhere, Category = "Pool")
	TArray<APoolableActor*> ObjectPool;

public:
	template <typename T>
	void InitPool(const int32 Size)
	{
		UClass* ObjectClass = T::StaticClass();
		for (int32 i = 0; i < Size; ++i) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			APoolableActor* NewActor = GetWorld()->SpawnActor<APoolableActor>(ObjectClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
			NewActor->Deactivate();
			ObjectPool.Add(NewActor);
		}
	}

	template <typename T>
	T* GetObject() {
		UClass* ObjectClass = T::StaticClass();
		for (APoolableActor* Object : ObjectPool)
		{
			if (!Object->GetIsActive())
			{
				Object->Activate();
				return Cast<T>(Object);
			}
		}

		// 풀에 사용 가능한 오브젝트가 없으면 새로 생성
		T* NewObject = GetWorld()->SpawnActor<T>(ObjectClass);
		ObjectPool.Add(NewObject);
		return NewObject;
	}

	template <typename T>
	void ReturnObject(T* Object) {
		Object->Deactivate();
	}
};
