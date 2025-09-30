// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/Tile/TheGameTile.h"

// Sets default values
ATheGameTile::ATheGameTile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Tile = CreateDefaultSubobject<USceneComponent>(TEXT("Tile"));
	Tile->SetupAttachment(RootComponent);

	LightPreset = CreateDefaultSubobject<USceneComponent>(TEXT("LightPreset"));
	LightPreset->SetupAttachment(Tile);
}

// Called when the game starts or when spawned
void ATheGameTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATheGameTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}