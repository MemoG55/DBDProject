// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/StreamableManager.h"
#include "Shared/DBDEnum.h"
#include "Shared/DBDStruct.h"
#include "LobbyLoadOutSlot.generated.h"

class UOverlay;
class ULobbyLoadOutSlotDesc;
class UBorder;
class UTextBlock;
class UImage;
class UButton;
class USizeBox;
class LobbyLoadOutSlot;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadOutSlotClicked, ELobbyLoadOutSlotType, SlotType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLobbyLoadOutPerkClicked, const FName&, DataRowName, const FPerkData&, PerkData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLobbyLoadOutItemClicked, const FName&, DataRowName, const FItemData&, ItemData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLobbyLoadOutAddOnClicked, const FName&, DataRowName, const FItemAddonData&, AddOnData);

/**
 * LoadOut Slot Base(Perk or AddOn or Item Slot)
 */
UCLASS()
class DBDPROJECT_API ULobbyLoadOutSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	~ULobbyLoadOutSlot();
protected:
	virtual void NativeConstruct() override;
public:
	FOnLoadOutSlotClicked OnLoadOutSlotClicked;
	FOnLobbyLoadOutPerkClicked OnLobbyLoadOutPerkClicked;
	FOnLobbyLoadOutItemClicked OnLobbyLoadOutItemClicked;
	FOnLobbyLoadOutAddOnClicked OnLobbyLoadOutAddOnClicked;

	TSharedPtr<FStreamableHandle> LoadHandle;

	UFUNCTION()
	void CreateToolTip(const FText& Text, const FText& ToolTip);

	UFUNCTION()
	void HandleEmptyOverlay(ESlateVisibility PVisibility);

	UFUNCTION()
	void HandleDataOverlay(ESlateVisibility PVisibility);

	UFUNCTION()
	void SetDataImage(UTexture2D* ImageData = nullptr);
	
	UFUNCTION()
	void SetData(const FPerkData SlotData);
	void SetData(const FItemData SlotData);
	void SetData(const FItemAddonData SlotData);


	UFUNCTION()
	void OnClickedSlot();

	UFUNCTION()
	void SetSlotType(ELobbyLoadOutSlotType Type);

	UFUNCTION()
	ELobbyLoadOutSlotType GetSlotType();
	
public:
	FName DataRowName;
	
	FPerkData* PerkData;

	FItemData* ItemData;

	FItemAddonData* ItemAddonData;
	
	UPROPERTY()
	TObjectPtr<UUserWidget> Data;


	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UOverlay> SlotEmptyOverlay;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> SlotBackgroundImage;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UOverlay> SlotDataOverlay;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> SlotDataImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> BlankImage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> BackgroundImage_Perk;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> BackgroundImage_Item;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> BackgroundImage_AddOn;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULobbyLoadOutSlotDesc> SlotDesc;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ULobbyLoadOutSlotDesc> LoadOutSlotDesc;
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<USizeBox> SlotContainer;

	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UButton> LoadOutRootButton;

	UPROPERTY()
	ELobbyLoadOutSlotType CurrentSlotType = ELobbyLoadOutSlotType::None;
};
