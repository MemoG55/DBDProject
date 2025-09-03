// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectSpawnManager.generated.h"

class AObjectSpawner;

UCLASS()
class DBDPROJECT_API AObjectSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectSpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Spawner")
	TMap<uint8, AObjectSpawner*> EscapeObjects;
	UPROPERTY(EditDefaultsOnly, Category = "Spawner")
	TMap<uint8, AObjectSpawner*> GeneratorObjects;
	UPROPERTY(EditDefaultsOnly, Category = "Spawner")
	TMap<uint8, AObjectSpawner*> HookObjects;
};
