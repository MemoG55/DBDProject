// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KMJ/Axe/PoolableActor.h"
#include "GenericObjectPool.generated.h"


UCLASS()
class DBDPROJECT_API AGenericObjectPool : public AActor
{
	GENERATED_BODY()
	
public:
	AGenericObjectPool();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Pool")
	TArray<UObject*> ObjectPool;
public:
	
	int32 idx = 0;

	template <typename ObjectClass>
	void InitPool(UClass* ObjectSubclass, int32 Size)
	{
		if (!ObjectSubclass) return;

		for (int32 i = 0; i < Size; ++i) 
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			// BP 클래스로 스폰
			ObjectClass* NewActor = GetWorld()->SpawnActor<ObjectClass>(ObjectSubclass, FVector(0,0,9999999), FRotator::ZeroRotator, SpawnParams);
			NewActor->Deactivate();
			ObjectPool.Add(NewActor);
		}
	}


	template <typename ObjectClass>
	ObjectClass* GetObject(UClass* ObjectSubclass)
	{
		if (!ObjectSubclass || ObjectPool.Num() == 0) return nullptr;
		
		for (UObject* Object : ObjectPool)
		{
			if (Object && !Cast<ObjectClass>(Object)->GetIsActive() && Object->IsA(ObjectSubclass))
			{
				return Cast<ObjectClass>(Object);
			}
		}

		// 순환 방식으로 반환
		UObject* NewObject = ObjectPool[idx];
		if (NewObject)
		{
			Cast<ObjectClass>(NewObject)->Deactivate();
			idx = (idx + 1) % ObjectPool.Num();
		}

		return Cast<ObjectClass>(NewObject);
	}

	template <typename ObjectClass>
	void ReturnObject(ObjectClass* Object) {
		Object->Deactivate();
	}
	
};
