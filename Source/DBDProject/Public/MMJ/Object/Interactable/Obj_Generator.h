// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/Interactable/DBDObject.h"
#include "MMJ/Object/Interface/EntitySpawnable.h"
#include "Obj_Generator.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API AObj_Generator : public ADBDObject, public IEntitySpawnable
{
	GENERATED_BODY()

public:
	AObj_Generator(const FObjectInitializer& ObjectInitializer);

	virtual void SpawnEntity() override;
	
protected:
	virtual void BeginPlay() override;
};
