// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/Axe/PoolableActor.h"


// Sets default values
APoolableActor::APoolableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APoolableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APoolableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoolableActor::Activate()
{
	IsActive = true;
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

void APoolableActor::Deactivate()
{
	IsActive = false;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}