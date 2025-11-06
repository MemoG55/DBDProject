// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Subsystem/DBDObjectObserver.h"

#include "MMJ/Object/Interactable/Obj_ExitDoor.h"
#include "MMJ/Object/Interactable/Obj_Generator.h"
#include "MMJ/Object/Interactable/Obj_Hook.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Component/InteractableComponent.h"
#include "Shared/GameFramework/DBDGameMode.h"
#include "Shared/GameFramework/DBDGameStateBase.h"


void UDBDObjectObserver::RegisterGenerator(AObj_Generator* Generator) 
{
	Generators.AddUnique(Generator);


	
	if (Generator->HasAuthority())
	{
		if (ADBDGameStateBase* DBDGameState = Cast<ADBDGameStateBase>(GetWorld()->GetGameState()))
		{
			DBDGameState->Generators.AddUnique(Generator);
			BindingGenerator(Cast<ADBDObject>(Generator));
		}
	}
}

void UDBDObjectObserver::RegisterHook(AObj_Hook* Hook) 
{
	Hooks.AddUnique(Hook);



	if (Hook->HasAuthority())
	{
		if (ADBDGameStateBase* DBDGameState = Cast<ADBDGameStateBase>(GetWorld()->GetGameState()))
		{
			DBDGameState->Hooks.AddUnique(Hook);
			BindingHook(Cast<ADBDObject>(Hook));
		}
	}
}

void UDBDObjectObserver::RegisterExitDoor(AObj_ExitDoor* ExitDoor) 
{
	ExitDoors.AddUnique(ExitDoor);
	
	if (ExitDoor->HasAuthority())
	{
		if (ADBDGameStateBase* DBDGameState = Cast<ADBDGameStateBase>(GetWorld()->GetGameState()))
		{
			DBDGameState->ExitDoors.AddUnique(ExitDoor);
			BindingExitDoor(ExitDoor);
		}
	}
}

TArray<AObj_Generator*> UDBDObjectObserver::GetGenerators() const
{
	return Generators;
	// if (ADBDGameStateBase* DBDGameState = Cast<ADBDGameStateBase>(GetWorld()->GetGameState()))
	// {
	// 	return DBDGameState->Generators;
	// }
	// return TArray<AObj_Generator*>();
}

TArray<AObj_Hook*> UDBDObjectObserver::GetHooks() const
{
	return Hooks;
	// if (ADBDGameStateBase* DBDGameState = Cast<ADBDGameStateBase>(GetWorld()->GetGameState()))
	// {
	// 	return DBDGameState->Hooks;
	// }
	// return TArray<AObj_Hook*>();
}

TArray<AObj_ExitDoor*> UDBDObjectObserver::GetExitDoors() const
{
	return ExitDoors;
	// if (ADBDGameStateBase* DBDGameState = Cast<ADBDGameStateBase>(GetWorld()->GetGameState()))
	// {
	// 	return DBDGameState->ExitDoors;
	// }
	// return TArray<AObj_ExitDoor*>();
}

TArray<AObj_Exit*> UDBDObjectObserver::GetExits() const
{
	return Exits;
	// if (ADBDGameStateBase* DBDGameState = Cast<ADBDGameStateBase>(GetWorld()->GetGameState()))
	// {
	// 	return DBDGameState->Exits;
	// }
	// return TArray<AObj_Exit*>();
}

void UDBDObjectObserver::BindingGenerator(ADBDObject* Generator)
{
	if (ADBDGameMode* DBDGameMode = Cast<ADBDGameMode>(GetWorld()->GetAuthGameMode()))
	{
		Generator->GetInteractableComponent()->OnCompleteInfo.AddDynamic(DBDGameMode, &ADBDGameMode::OnGeneratorComplete);
		Generator->GetInteractableComponent()->OnInteractInfo.AddDynamic(DBDGameMode, &ADBDGameMode::OnGeneratorInteract);
	}
}

void UDBDObjectObserver::UnBindingGenerator(ADBDObject* Generator)
{
	if (ADBDGameMode* DBDGameMode = Cast<ADBDGameMode>(GetWorld()->GetAuthGameMode()))
	{
		Generator->GetInteractableComponent()->OnCompleteInfo.RemoveAll(DBDGameMode);
		Generator->GetInteractableComponent()->OnInteractInfo.RemoveAll(DBDGameMode);
	}
}

void UDBDObjectObserver::BindingExitDoor(ADBDObject* ExitDoor)
{
	if (ADBDGameMode* DBDGameMode = Cast<ADBDGameMode>(GetWorld()->GetAuthGameMode()))
	{
		ExitDoor->GetInteractableComponent()->OnComplete.AddDynamic(DBDGameMode, &ADBDGameMode::SetEscapeTimer);
		ExitDoor->GetInteractableComponent()->OnDestroy.AddDynamic(DBDGameMode, &ADBDGameMode::EndGameState);
	}
}

void UDBDObjectObserver::UnBindingExitDoor(ADBDObject* ExitDoor)
{
	if (ADBDGameMode* DBDGameMode = Cast<ADBDGameMode>(GetWorld()->GetAuthGameMode()))
	{
		ExitDoor->GetInteractableComponent()->OnComplete.RemoveAll(DBDGameMode);
		ExitDoor->GetInteractableComponent()->OnDestroy.RemoveAll(DBDGameMode);
	}
}

void UDBDObjectObserver::BindingHook(ADBDObject* Hook)
{
}

void UDBDObjectObserver::UnBindingHook(ADBDObject* Hook)
{
}

void UDBDObjectObserver::ActivateExitDoors()
{
	if (ADBDGameStateBase* DBDGameState = Cast<ADBDGameStateBase>(GetWorld()->GetGameState()))
	{
		for (const AObj_ExitDoor* ExitDoor : DBDGameState->ExitDoors)
		{
			if (!ExitDoor->GetInteractableComponent()->IsActive())
			{
				ExitDoor->GetInteractableComponent()->StartInteraction(nullptr);
			}
		}
	}
	OnExitDoorActivated.Broadcast();
}
