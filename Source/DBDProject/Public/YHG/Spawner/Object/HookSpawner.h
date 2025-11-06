// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HookSpawner.generated.h"

class AObj_Hook;

UCLASS()
class DBDPROJECT_API AHookSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHookSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AObj_Hook> HookObject;

	UPROPERTY(EditDefaultsOnly)
	FVector SpawnLocation;

	UPROPERTY(EditDefaultsOnly)
	FRotator SpawnRotation;
	
public:
	void SpawnHook();
};
