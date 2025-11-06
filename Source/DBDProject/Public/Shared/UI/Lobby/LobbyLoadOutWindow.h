// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Shared/DBDEnum.h"
#include "LobbyLoadOutWindow.generated.h"

class ADBDPlayerState;
class ULobbyLoadOutSlot;
class UButton;
class ULobbyLoadOutList;
class UGridPanel;
/**
 * LoadOut Shift Overlay
 */
UCLASS()
class DBDPROJECT_API ULobbyLoadOutWindow : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	UFUNCTION()
	void HandleLoadOutWindow(ELobbyLoadOutSlotType SlotType);

	UFUNCTION()
	void UpdateLoadOutWindow();
public:

	UFUNCTION()
	void BindingGameState();
	
	UFUNCTION()
	void BindingPlayerState(ADBDPlayerState* CurrentPS);

	UFUNCTION()
	void BindingPlayerController();

	UFUNCTION()
	void BindingSelf();

	UFUNCTION()
	FName FindDataByRowName(ELobbyLoadOutSlotType Type, const FName& RowName);
public:
	UFUNCTION()
	void ExitWindow();

	UFUNCTION()
	void HandleKillerVisibility();

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UGridPanel> PerkSlotList;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UGridPanel> ItemContainer;
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UGridPanel> ItemSlotList;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UGridPanel> AddOnSlotList;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<ULobbyLoadOutList> LoadOutList;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UButton>  BtnLoadOutListExit;
};
