// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

#include "MMJ/Object/Interactable/DBDObject.h"
#include "MMJ/Object/Interactable/Obj_Generator.h"
#include "MMJ/Object/Interactable/Obj_Hook.h"
#include "MMJ/Object/Interactable/Obj_Entity.h"
#include "MMJ/Object/Interactable/Obj_Exit.h"
#include "MMJ/Object/Interactable/Obj_ExitDoor.h"
#include "DBDObjectObserver.generated.h"


/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FExitDoorActivatedDelegate);

UCLASS()
class DBDPROJECT_API UDBDObjectObserver : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	void RegisterGenerator(AObj_Generator* Generator) ;
	void RegisterHook(AObj_Hook* Hook) ;
	void RegisterExitDoor(AObj_ExitDoor* ExitDoor) ;

	UFUNCTION(BlueprintPure)
	TArray<AObj_Generator*> GetGenerators() const;

	UFUNCTION(BlueprintPure)
	TArray<AObj_Hook*> GetHooks() const;

	UFUNCTION(BlueprintPure)
	TArray<AObj_ExitDoor*> GetExitDoors() const;

	UFUNCTION(BlueprintPure)
	TArray<AObj_Exit*> GetExits() const;

	UFUNCTION()
	void BindingGenerator(ADBDObject* Generator);

	UFUNCTION()
	void UnBindingGenerator(ADBDObject* Generator);

	UFUNCTION()
	void BindingExitDoor(ADBDObject* ExitDoor);

	UFUNCTION()
	void UnBindingExitDoor(ADBDObject* ExitDoor);

	UFUNCTION()
	void BindingHook(ADBDObject* Hook);

	UFUNCTION()
	void UnBindingHook(ADBDObject* Hook);

	UFUNCTION()
	void ActivateExitDoors();

	FExitDoorActivatedDelegate OnExitDoorActivated;
protected:
	UPROPERTY()
	TArray<TObjectPtr<AObj_Generator>> Generators;

	UPROPERTY()
	TArray<TObjectPtr<AObj_Hook>> Hooks;

	UPROPERTY()
	TArray<TObjectPtr<AObj_ExitDoor>> ExitDoors;

	UPROPERTY()
	TArray<TObjectPtr<AObj_Exit>> Exits;
	
};
