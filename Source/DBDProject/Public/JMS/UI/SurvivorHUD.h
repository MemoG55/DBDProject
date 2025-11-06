// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/UI/DBDHUD.h"
#include "SurvivorHUD.generated.h"

class USurvivorItemHUD;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API USurvivorHUD : public UDBDHUD
{
	GENERATED_BODY()
public:
	//KMJ_1016_ItemHUD
	UPROPERTY(BlueprintReadWrite, Category = "SurvivorHUD", meta = (BindWidget))
	USurvivorItemHUD* SurvivorItemHUD;
	
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurvivorHUD")
	// UDataTable* AddonTable;
	//
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurvivorHUD")
	// UDataTable* ItemTable;

	virtual void NativeConstruct() override;
	//
	// virtual void SetAddons(ADBDCharacter* Character) override;
	// UFUNCTION()
	// virtual void SetItemHUD(ADBDCharacter* Character) override;
	
	// UFUNCTION()
	// void ClearItemIcon();
};
