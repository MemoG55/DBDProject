// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/DBDObject.h"
#include "Obj_ExitDoor.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API AObj_ExitDoor : public ADBDObject
{
	GENERATED_BODY()

public:
	virtual bool CanInteraction(AActor* Actor) override;
	
};
