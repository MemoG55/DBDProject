// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/Perk/PerkComponent.h"
#include "Perk_Empathy.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UPerk_Empathy : public UPerkComponent
{
	GENERATED_BODY()
	
public:
	UPerk_Empathy();
	virtual void OnServerSideInitialized() override;
	virtual void OnOwnerClientSideInitialized() override;
	
};
