// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/GAS/GE/ObjGameplayEffect.h"
#include "ObjGE_Init.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UObjGE_Init : public UObjGameplayEffect
{
	GENERATED_BODY()
public:
	UObjGE_Init();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxTask;
};
