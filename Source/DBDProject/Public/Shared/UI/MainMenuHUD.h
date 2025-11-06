// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuHUD.generated.h"

class UMainMenuSurvivorItemSlot;
class UWrapBox;
class UEditableTextBox;
class UButton;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UMainMenuHUD : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	UButton* CreateSessionButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinSessionButton;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess, BindWidget))
	UEditableTextBox* IPTextBox;

	UPROPERTY(meta = (BindWidget))
	UButton* IPJoinButton;

	UPROPERTY(meta = (BindWidget))
	UWrapBox* ItemWrapBox;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* SurvivorItemDatas;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainMenuSurvivorItemSlot> MainMenuSurvivorItemSlotClass;

	UPROPERTY()
	TArray<UMainMenuSurvivorItemSlot*> MainMenuSurvivorItemSlots;

public:
	UFUNCTION(Server, Reliable)
	void SetSurvivorItem(FName SurvivorItem);
};
