// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Shared/DBDEnum.h"
#include "LobbyLoadOutList.generated.h"

class UBasePerkIcon;
class UAddonIcon;
class ULobbyItemIcon;
class ULobbyPerkIcon;
class ULobbyLoadOutSlot;
class ADBDPlayerState;
class UGridPanel;

/**
 * LoadOut List (Perk or AddOn or Item List)
 */
UCLASS()
class DBDPROJECT_API ULobbyLoadOutList : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void BindingPlayerState();

	UFUNCTION()
	void BindingPlayerController();

	// MainSlotList Update
	UFUNCTION()
	void HandleLoadOutList(ADBDPlayerState* PlayerState, ELobbyLoadOutSlotType Type);

	UFUNCTION()
	ELobbyLoadOutSlotType GetCurrentListType();

	// DB Load
	UFUNCTION()
	void OnAddOnLoaded();

	UFUNCTION()
	void OnItemLoaded();

	UFUNCTION()
	void OnKillerPerkLoaded();

	UFUNCTION()
	void OnSurvivorPerkLoaded();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby Load Out")
	TSubclassOf<ULobbyLoadOutSlot> LoadOutSlotClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby Load Out")
	TSubclassOf<UBasePerkIcon> PerkSlotClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby Load Out")
	TSubclassOf<ULobbyItemIcon> ItemSlotClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lobby Load Out")
	TSubclassOf<UAddonIcon> AddOnSlotClass;
private:
	UPROPERTY()
	TObjectPtr<UDataTable> SurvivorPerkData;

	UPROPERTY()
	TObjectPtr<UDataTable> KillerPerkData;
	
	UPROPERTY()
	TObjectPtr<UDataTable> SurvivorItemData;
	
	UPROPERTY()
	TObjectPtr<UDataTable> SurvivorAddOnData;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UGridPanel> LoadOutListContainer;

	int32 Row = 3, Column = 5;

	UPROPERTY()
	ELobbyLoadOutSlotType CurrentListType = ELobbyLoadOutSlotType::None;
};
