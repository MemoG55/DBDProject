// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DBDObjectPool.generated.h"

class ADBDPoolEntryObject;

UCLASS()
class DBDPROJECT_API ADBDObjectPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADBDObjectPool();

	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	ADBDPoolEntryObject* SpawnPooledObject(APawn* InInstigator);
	
	UPROPERTY(EditAnywhere, Category = "Object Pool")
	TSubclassOf<ADBDPoolEntryObject> PooledObjectClass;
	
	UPROPERTY(EditAnywhere, Category = "Object Pool")
	int PoolSize = 20;
	
	UPROPERTY(EditAnywhere, Category = "Object Pool")
	float PooledObjectLifeTime = 20.0f;

	UFUNCTION()
	void OnPooledObjectDespawn(ADBDPoolEntryObject* PoolActor);

	void DeactivateAllPooledObjects();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<ADBDPoolEntryObject*> ObjectPool;
	TArray<int> SpawnedPoolIndexes;

	
	
};
