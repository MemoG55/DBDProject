// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivorItemPickupWidget.generated.h"

struct FGameplayTag;
class ASurvivorItem;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API USurvivorItemPickupWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	UPROPERTY()
	ASurvivorItem* NearbyItem;

	void OnItemInteractableTagChanged(const FGameplayTag Tag, int32 NewCount);
	UPROPERTY(EditDefaultsOnly, Category = "SurvivorItemPickupWidget")
	UDataTable* ItemDataTable;
	
};
