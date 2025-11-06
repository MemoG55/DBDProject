// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/Interactable/DBDObject.h"
#include "Shared/Interface/Combinable.h"
#include "Obj_ExitDoor.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API AObj_ExitDoor : public ADBDObject, public ICombinable
{
	GENERATED_BODY()

public:
	AObj_ExitDoor(const FObjectInitializer& ObjectInitializer);

	virtual void CreateCombinedActor() override;

	virtual AActor* GetCombinedActor() const override;
	
protected:
	virtual void BeginPlay() override;
};
