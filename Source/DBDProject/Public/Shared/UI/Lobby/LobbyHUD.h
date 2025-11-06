// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyHUD.generated.h"

class ADBDPlayerState;
class ULobbyLoadOutWindow;
class ALobbyPlayerController;
class UDBDDataBase;
class UButton;
class UHorizontalBox;
class UTextBlock;
class ULobbyPlayerSlot;
class UGridPanel;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API ULobbyHUD : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY()
	TObjectPtr<UDBDDataBase> DBDDataBase;

	UPROPERTY()
	TObjectPtr<ALobbyPlayerController> OwningController;

public:
	UFUNCTION()
	void BindingGameState();

	UFUNCTION()
	void BindingOtherPlayerState(ADBDPlayerState* OtherPS);
	UFUNCTION()
	void BindingPlayerState(ADBDPlayerState* CurrentPS);

	UFUNCTION()
	void BindingPlayerController();

	UFUNCTION()
	void BindingSelf();

	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UButton> Button_HandleReady;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TBReadyState;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UButton> Button_HandleRole;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TBRoleState;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UButton> Button_HandleLoadout;
	
	
	UFUNCTION()
	void OnRep_OnReadyStateUpdatedFromSelf();
	UFUNCTION()
	void OnRep_OnPlayerStateUpdatedFromGameState();
	UFUNCTION()
	void OnRep_OnPlayerStateUpdatedFromSelf();
	UFUNCTION()
	void OnRep_OnPlayerStateUpdatedFromOther(ADBDPlayerState* OtherPS);

	UFUNCTION()
	void HandleLoadOut();

	UFUNCTION()
	void HandlePlayerSlot(ADBDPlayerState* PS = nullptr);

	UFUNCTION()
	ULobbyLoadOutWindow* GetLoadOutWindow();


private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<ULobbyPlayerSlot> KillerPlayerSlot;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UGridPanel> PlayerSlotContainer;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TObjectPtr<ULobbyPlayerSlot>> SurvivorPlayerSlots;

	UPROPERTY()
	TArray<TObjectPtr<UUserWidget>> ActiveLoadOutStack;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<ULobbyLoadOutWindow> LoadOutWindow;
	
};
