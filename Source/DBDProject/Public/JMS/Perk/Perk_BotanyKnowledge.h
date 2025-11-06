// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/Perk/PerkComponent.h"
#include "Perk_BotanyKnowledge.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UPerk_BotanyKnowledge : public UPerkComponent
{
	GENERATED_BODY()

public:
	UPerk_BotanyKnowledge();
	virtual void OnServerSideInitialized() override;
	
	
	
};
