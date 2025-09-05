// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/DBDObject.h"
#include "Obj_Generator.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API AObj_Generator : public ADBDObject
{
	GENERATED_BODY()

public:
	AObj_Generator();
	virtual void StartInteraction(AActor* Actor) override;

	virtual void TickInteraction(AActor* Actor) override;

	virtual float GetTaskSpeedOfInteractors() const override;

	virtual void BeginPlay() override;
	
};
