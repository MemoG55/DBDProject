// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/Perk/PerkComponent.h"
#include "Perk_Bond.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UPerk_Bond : public UPerkComponent
{
	GENERATED_BODY()
public:
	UPerk_Bond();
	virtual void OnServerSideInitialized() override;
	virtual void OnOwnerClientSideInitialized() override;
	
	
	
};
