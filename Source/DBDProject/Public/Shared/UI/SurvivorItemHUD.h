// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivorItemHUD.generated.h"

class USurvivorItemIcon;
class UAddonIcon;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API USurvivorItemHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "KillerHUD", meta = (BindWidget))
	TObjectPtr<USurvivorItemIcon> SurvivorIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "KillerHUD", meta = (BindWidget))
	TObjectPtr<UAddonIcon> AddonIcon1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "KillerHUD", meta = (BindWidget))
	TObjectPtr<UAddonIcon> AddonIcon2;

	// UFUNCTION()
	// void SetAddonIcons(FItemAddonData Addon1, FItemAddonData Addon2);
protected:
	virtual void NativeConstruct() override;
};
