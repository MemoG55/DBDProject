// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuSurvivorItemSlot.generated.h"

class UTextBlock;
class UButton;
class USizeBox;

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UMainMenuSurvivorItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	USizeBox* SizeBox;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess, BindWidget))
	UButton* Button;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess, BindWidget))
	UTextBlock* TextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
	FName SurvivorItem;

public:
	void SetSurvivorItem(FName NewSurvivorItem);
	
	void SetTextBlock_Text(FText Text) const;

	UFUNCTION()
	void Button_Click();
};
