// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/Component/ICObject.h"
#include "IC_Entity.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UIC_Entity : public UICObject
{
	GENERATED_BODY()

public:
	virtual void FinishInteraction(AActor* Actor) override;
	
};
