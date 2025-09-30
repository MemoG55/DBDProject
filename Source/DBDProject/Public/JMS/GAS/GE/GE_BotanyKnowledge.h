// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GE_BotanyKnowledge.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGE_BotanyKnowledge : public UGameplayEffect
{
	GENERATED_BODY()
public:
	UGE_BotanyKnowledge();
	float HealSpeedMultiplier = 1.5f;
	
	
};
