// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PerkWidget.generated.h"

class UPerkComponent;
class ASurvivorItem;
class UImage;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UPerkWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta = (BindWidget))
	UImage* Perk1Icon;
	UPROPERTY(meta = (BindWidget))
	UImage* Perk2Icon;
	UPROPERTY(meta = (BindWidget))
	UImage* Perk3Icon;
	UPROPERTY(meta = (BindWidget))
	UImage* Perk4Icon;
public:
	UFUNCTION()
	void SetPerkIcon(UPerkComponent* NewPerk1, UPerkComponent* NewPerk2, UPerkComponent* NewPerk3, UPerkComponent* NewPerk4);
protected:
	virtual void NativeConstruct() override;
	UPROPERTY()
	UDataTable* PerkDataTable;

	void OnDataTableLoaded();
	
	
	
};
