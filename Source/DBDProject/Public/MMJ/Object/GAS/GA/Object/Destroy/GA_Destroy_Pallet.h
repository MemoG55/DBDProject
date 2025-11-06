// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/GAS/GA/Object/GA_Destroy.h"
#include "GA_Destroy_Pallet.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Destroy_Pallet : public UGA_Destroy
{
	GENERATED_BODY()

protected:
	virtual void ExecuteGameplayEffectAndCue(FGameplayEventData Data) override;
	
};
