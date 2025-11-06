// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ICObject.h"
#include "IC_Generator.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UIC_Generator : public UICObject
{
	GENERATED_BODY()
public:
	UIC_Generator();
	virtual void StartInteraction(AActor* Actor) override;
	virtual void CompleteInteraction(AActor* Actor) override;

public:
	virtual bool CanInteraction(AActor* Actor) override;
	
};
