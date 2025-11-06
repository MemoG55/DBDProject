// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "KillerSkillHUD.generated.h"

struct FKillerLoadout;
struct FItemAddonData;
class UGA_Hook_Killer;
class UGA_Drop;
class UGA_Carry;
class UBaseSquareIcon;
class UAddonIcon;
class UKillerSkillIcon;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UKillerSkillHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "KillerHUD", meta = (BindWidget))
	UKillerSkillIcon* KillerSkillIcon;

	UPROPERTY(BlueprintReadWrite, Category = "KillerHUD", meta = (BindWidget))
	UAddonIcon* SkillAddonIcon1;
	UPROPERTY(BlueprintReadWrite, Category = "KillerHUD", meta = (BindWidget))
	UAddonIcon* SkillAddonIcon2;
	
	UFUNCTION()
	void SetAddonIcons(FItemAddonData Addon1, FItemAddonData Addon2);
};
