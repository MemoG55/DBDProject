// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheGameTile.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API ATheGameTile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATheGameTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	TObjectPtr<USceneComponent> Tile;

	UPROPERTY()
	TObjectPtr<USceneComponent> LightPreset;
};
