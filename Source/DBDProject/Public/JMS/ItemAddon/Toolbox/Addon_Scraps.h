// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/ItemAddon/ItemAddonComponent.h"
#include "Addon_Scraps.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UAddon_Scraps : public UItemAddonComponent
{
	GENERATED_BODY()
protected:
	virtual void OnInitialized_Implementation() override;
};
