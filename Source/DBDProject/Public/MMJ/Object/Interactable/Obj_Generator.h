// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/Interactable/DBDObject.h"
#include "Obj_Generator.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API AObj_Generator : public ADBDObject
{
	GENERATED_BODY()

public:
	AObj_Generator(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	
};
