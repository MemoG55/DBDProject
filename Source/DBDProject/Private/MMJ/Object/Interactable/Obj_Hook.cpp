// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Interactable/Obj_Hook.h"

#include "MMJ/Object/Component/IC_Hook.h"
#include "MMJ/Object/Spawner/EntitySpawner.h"
#include "MMJ/Object/Subsystem/EntitySpawnSubsystem.h"
#include "Net/UnrealNetwork.h"
#include "Shared/Subsystem/DBDObjectObserver.h"

AObj_Hook::AObj_Hook(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UIC_Hook>(ADBDObject::InteractableComponentName))
{
}

void AObj_Hook::SpawnEntity()
{
	if (UEntitySpawnSubsystem* EntitySpawnSubsystem = GetWorld()->GetSubsystem<UEntitySpawnSubsystem>())
	{
		if (AEntitySpawner* EntitySpawner = EntitySpawnSubsystem->GetEntitySpawner())
		{
			Entity = EntitySpawner->SpawnEntity(this, GetInteractableComponent()->InteractableTag);
		}
	}
}

void AObj_Hook::BeginPlay()
{
	Super::BeginPlay();
	
	
	if (UDBDObjectObserver* ObjectObserver = GetWorld()->GetSubsystem<UDBDObjectObserver>())
	{
		ObjectObserver->RegisterHook(this);
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
	
}

void AObj_Hook::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(AObj_Hook, HookPhase, COND_None, REPNOTIFY_Always);
}

void AObj_Hook::SetHookPhase(EHookPhase Phase)
{
	HookPhase = Phase;
}

EHookPhase AObj_Hook::GetHookPhase() const
{
	return HookPhase;
}

