// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/Spawner/Object/HookSpawner.h"

#include "MMJ/Object/Interactable/Obj_Hook.h"

// Sets default values
AHookSpawner::AHookSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AHookSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHookSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHookSpawner::SpawnHook()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;

	FVector SpawnWorldLocation = GetActorLocation() + GetActorRotation().RotateVector(SpawnLocation);
	FRotator SpawnWorldRotation = (GetActorQuat() * SpawnRotation.Quaternion()).Rotator();
	
	GetWorld()->SpawnActor<AObj_Hook>(HookObject, SpawnWorldLocation, SpawnWorldRotation, SpawnParameters);
}

