// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivorItemSlot.generated.h"

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
class DBDPROJECT_API USurvivorItemSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION()
	void OnLoadoutChanged(FSurvivorLoadout Loadout);
	UFUNCTION()
	void OnItemChanged(ASurvivorItem* EquippedItem);

	UPROPERTY()
	ASurvivorItem* CachedItem;

private:
	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;
	ASurvivorCharacter* CachedSurvivorCharacter;
	UDBDGameInstance* CachedGI;
	
};
