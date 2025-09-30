// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/Interactable/DBDObject.h"
#include "Obj_ExitDoor.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API AObj_ExitDoor : public ADBDObject
{
	GENERATED_BODY()

public:
	AObj_ExitDoor(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	// UChildActorComponent* ChildActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ADBDObject> ExitZone;

	UFUNCTION()
	void CreateExitZone();
	
};
