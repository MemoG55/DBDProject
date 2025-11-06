// Fill out your copyright notice in the Description page of Project Settings.
// TODO: JMS: 데디에서는 오라가 적용이 안됨...

#include "MMJ/Object/Interactable/Obj_Generator.h"

#include "Components/WidgetComponent.h"
#include "MMJ/Object/Component/IC_Generator.h"
#include "MMJ/Object/Spawner/EntitySpawner.h"
#include "MMJ/Object/Subsystem/EntitySpawnSubsystem.h"
#include "Shared/DBDEnum.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/Subsystem/DBDObjectObserver.h"


AObj_Generator::AObj_Generator(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UIC_Generator>(ADBDObject::InteractableComponentName))
{
	
}

void AObj_Generator::SpawnEntity()
{
	if (UEntitySpawnSubsystem* EntitySpawnSubsystem = GetWorld()->GetSubsystem<UEntitySpawnSubsystem>())
	{
		if (AEntitySpawner* EntitySpawner = EntitySpawnSubsystem->GetEntitySpawner())
		{
			Entity = EntitySpawner->SpawnEntity(this, GetInteractableComponent()->InteractableTag);
		}
	}
}

void AObj_Generator::BeginPlay()
{
	Super::BeginPlay();
	
	if (UDBDObjectObserver* ObjectObserver = GetWorld()->GetSubsystem<UDBDObjectObserver>())
	{
		ObjectObserver->RegisterGenerator(this);
	}
		if (HasAuthority())
		{
	FTimerHandle  TimerHandle;
	GetWorldTimerManager().SetTimer(
		TimerHandle,
		FTimerDelegate::CreateLambda([&]()
		{
			SpawnEntity();
			
		}),
		1.f,
		false);
			
		}

	if (WidgetComponent)
	{
		WidgetComponent->SetVisibility(false);
	}

	
}

