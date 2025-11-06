// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlot.generated.h"

class ASurvivorItem;
/**
 * 
 */
class UImage;
UCLASS()
class DBDPROJECT_API UItemSlot : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;
public:
	UFUNCTION()
	void SetItemIcon(ASurvivorItem* NewItem);
protected:
	virtual void NativeConstruct() override;
	UPROPERTY()
	UDataTable* ItemDataTable;

	void OnDataTableLoaded();
};
