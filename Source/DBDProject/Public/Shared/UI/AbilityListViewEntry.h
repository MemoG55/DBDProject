// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "AbilityListViewEntry.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UAbilityListViewEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UImage* KeyIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AbilityDescriptionText;
};
