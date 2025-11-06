// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Interactable/Obj_Pallet.h"

#include "MMJ/Object/Component/IC_Pallet.h"
#include "MMJ/Object/Spawner/EntitySpawner.h"
#include "MMJ/Object/Subsystem/EntitySpawnSubsystem.h"

AObj_Pallet::AObj_Pallet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UIC_Pallet>(InteractableComponentName))
{
	Pallet_Broken = CreateDefaultSubobject<UStaticMeshComponent>("Pallet_Broken");
	Pallet_Broken->SetupAttachment(GetRootComponent());

	Pallet_Broken_Disappear = CreateDefaultSubobject<UStaticMeshComponent>("Pallet_Broken_Disappear");
	Pallet_Broken_Disappear->SetupAttachment(GetRootComponent());
}

void AObj_Pallet::SpawnEntity()
{
	if (UEntitySpawnSubsystem* EntitySpawnSubsystem = GetWorld()->GetSubsystem<UEntitySpawnSubsystem>())
	{
		if (AEntitySpawner* EntitySpawner = EntitySpawnSubsystem->GetEntitySpawner())
		{
			Entity = EntitySpawner->SpawnEntity(this, GetInteractableComponent()->InteractableTag);
		}
	}
}


void AObj_Pallet::BeginPlay()
{
	Super::BeginPlay();

	Pallet_Broken->SetVisibility(false);
	Pallet_Broken_Disappear->SetVisibility(false);
}


void AObj_Pallet::OnRep_IsDestroyed()
{
	Super::OnRep_IsDestroyed();
	
	ObjectMesh->SetVisibility(false);
	Pallet_Broken_Disappear->SetVisibility(true);
	Pallet_Broken->SetVisibility(true);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		FTimerDelegate::CreateLambda([this]()
		{
			Pallet_Broken_Disappear->SetVisibility(false);
		}),
		3.f,
		false
		);
}
