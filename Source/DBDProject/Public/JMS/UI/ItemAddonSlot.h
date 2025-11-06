// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "ItemAddonSlot.generated.h"

class ASurvivorItem;
class UImage;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UItemAddonSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void SetAddonIcon(ASurvivorItem* NewItem);

protected:
	virtual void NativeConstruct() override;

	void OnDataTableLoaded();
private:
	UPROPERTY(meta = (BindWidget))
	UImage* Addon1Icon;
	UPROPERTY(meta = (BindWidget))
	UImage* Addon2Icon;
	
	UPROPERTY()
	UDataTable* AddonDataTable;
	
	
};
