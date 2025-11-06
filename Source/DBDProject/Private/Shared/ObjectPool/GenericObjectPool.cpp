// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/ObjectPool/GenericObjectPool.h"


// Sets default values
AGenericObjectPool::AGenericObjectPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGenericObjectPool::BeginPlay()
{
	Super::BeginPlay();
	
}

