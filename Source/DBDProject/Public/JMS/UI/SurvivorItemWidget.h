// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivorItemWidget.generated.h"

class UItemSlot;
class UItemAddonSlot;
class UVerticalBox;
class ASurvivorItem;
class ASurvivorCharacter;
class UDBDGameInstance;
class ADBDPlayerState;
class UImage;
struct FSurvivorLoadout;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API USurvivorItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

protected:
	// UFUNCTION()
	// void OnItemChanged(ASurvivorItem* EquippedItem);

	UPROPERTY()
	ASurvivorItem* CachedItem;

private:
	UPROPERTY(meta = (BindWidget))
	UItemSlot* ItemSlot;
	UPROPERTY(meta = (BindWidget))
	UItemAddonSlot* AddonSlot;
	UPROPERTY()
	ASurvivorCharacter* CachedSurvivorCharacter;
	
};
