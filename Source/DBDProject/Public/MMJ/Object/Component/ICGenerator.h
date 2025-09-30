// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ICObject.h"
#include "ICGenerator.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UICGenerator : public UICObject
{
	GENERATED_BODY()
public:
	UICGenerator();
protected:
	virtual void StartInteraction(AActor* Actor) override;
	virtual void TickInteraction(AActor* Actor) override;

	virtual void UnSetInteractors(AActor* Actor) override;

public:
	virtual bool CanInteraction(AActor* Actor) override;
	
};
