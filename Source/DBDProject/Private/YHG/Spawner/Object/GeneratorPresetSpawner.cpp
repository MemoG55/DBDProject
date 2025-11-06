// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/Spawner/Object/GeneratorPresetSpawner.h"

// Sets default values
AGeneratorPresetSpawner::AGeneratorPresetSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGeneratorPresetSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGeneratorPresetSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGeneratorPresetSpawner::SpawnGeneratorPreset()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	GetWorld()->SpawnActor<AActor>(TargetGeneratorPreset, GetActorLocation(), GetActorRotation(),SpawnParameters);
}

