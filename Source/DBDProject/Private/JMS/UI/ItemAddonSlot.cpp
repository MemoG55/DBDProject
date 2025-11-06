// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/UI/ItemAddonSlot.h"

#include "Components/Image.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/Item/SurvivorItem.h"
#include "JMS/ItemAddon/ItemAddonComponent.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DataAsset/DBDDataBase.h"
#include "Shared/GameFramework/DBDGameInstance.h"
#include "Shared/UI/DBDWidgetComponent.h"


void UItemAddonSlot::SetAddonIcon(ASurvivorItem* NewItem)
{
	if (!AddonDataTable || !NewItem)
	{
		SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	if (NewItem->GetAddon1() && Addon1Icon && Addon2Icon)
	{
		FItemAddonData* ItemAddonData = AddonDataTable->FindRow<FItemAddonData>(NewItem->GetAddon1()->GetAddonID(), "");
		if (ItemAddonData)
		{
			SetVisibility(ESlateVisibility::Visible);
			Addon1Icon->SetBrushFromSoftTexture(ItemAddonData->Icon);
			Addon1Icon->SetDesiredSizeOverride(FVector2D(33.f,33.f));
			Addon1Icon->SetBrushTintColor(FSlateColor(FLinearColor::White));
		}
	}
	if (NewItem->GetAddon2() && Addon1Icon && Addon2Icon)
	{
		FItemAddonData* ItemAddonData = AddonDataTable->FindRow<FItemAddonData>(NewItem->GetAddon2()->GetAddonID(), "");
		if (ItemAddonData)
		{
			SetVisibility(ESlateVisibility::Visible);
			Addon2Icon->SetBrushFromSoftTexture(ItemAddonData->Icon);
			Addon2Icon->SetDesiredSizeOverride(FVector2D(33.f,33.f));
			Addon2Icon->SetBrushTintColor(FSlateColor(FLinearColor::White));
		}
	}
}

void UItemAddonSlot::NativeConstruct()
{
	Super::NativeConstruct();
	UDBDGameInstance* GI = GetGameInstance<UDBDGameInstance>();
	if (!GI)
	{
		return;
	}
	FSoftObjectPath AssetPath = GI->DBDDB->ItemAddonDB.ToSoftObjectPath();

	if (AssetPath.IsValid())
	{
		UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
			AssetPath, FStreamableDelegate::CreateUObject(this, &UItemAddonSlot::OnDataTableLoaded));
	}
	ASurvivorCharacter* Survivor = GetOwningPlayerPawn<ASurvivorCharacter>();
	if (Survivor)
	{
		// JMS: UI수정: WidgetComponent에서 관리
		// Survivor->EquippedItemChangedDelegate.AddDynamic(this, &UItemAddonSlot::SetAddonIcon);
		Survivor->GetWidgetComponent()->OnUpdateEquippedItem.AddDynamic(this, &UItemAddonSlot::SetAddonIcon);
		SetAddonIcon(Survivor->GetEquippedItem());
	}
}

void UItemAddonSlot::OnDataTableLoaded()
{
	UDBDGameInstance* GI = GetGameInstance<UDBDGameInstance>();
	if (!GI)
	{
		return;
	}
	UObject* LoadedObject = GI->DBDDB->ItemAddonDB.Get();
	if (LoadedObject)
	{
		AddonDataTable = Cast<UDataTable>(LoadedObject);
	}
}
