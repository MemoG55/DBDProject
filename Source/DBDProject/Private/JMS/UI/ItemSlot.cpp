// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/UI/ItemSlot.h"

#include "Components/Image.h"
#include "Shared/DBDStruct.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/Item/SurvivorItem.h"
#include "Shared/DataAsset/DBDDataBase.h"
#include "Shared/GameFramework/DBDGameInstance.h"
#include "Shared/UI/DBDWidgetComponent.h"


void UItemSlot::SetItemIcon(ASurvivorItem* NewItem)
{
	if (!ItemDataTable|| !NewItem)
	{
		SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	FItemData* ItemData = ItemDataTable->FindRow<FItemData>(NewItem->GetItemID(), "");
	if (ItemData&&ItemIcon)
	{
		SetVisibility(ESlateVisibility::Visible);
		ItemIcon->SetBrushFromSoftTexture(ItemData->Icon);
		ItemIcon->SetDesiredSizeOverride(FVector2D(200.f,200.f));
		ItemIcon->SetBrushTintColor(FSlateColor(FLinearColor::White));
	}
}


void UItemSlot::NativeConstruct()
{
	Super::NativeConstruct();
	UDBDGameInstance* GI = GetGameInstance<UDBDGameInstance>();
	if (!GI)
	{
		return;
	}
	FSoftObjectPath AssetPath = GI->DBDDB->SurvivorItemDB.ToSoftObjectPath();

	if (AssetPath.IsValid())
	{
		UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
			AssetPath, FStreamableDelegate::CreateUObject(this, &UItemSlot::OnDataTableLoaded));
	}
	ASurvivorCharacter* Survivor = GetOwningPlayerPawn<ASurvivorCharacter>();
	if (Survivor)
	{
		Survivor->GetWidgetComponent()->OnUpdateEquippedItem.AddDynamic(this, &UItemSlot::SetItemIcon);
		SetItemIcon(Survivor->GetEquippedItem());
	}
}

void UItemSlot::OnDataTableLoaded()
{
	UDBDGameInstance* GI = GetGameInstance<UDBDGameInstance>();
	if (!GI)
	{
		return;
	}
	UObject* LoadedObject = GI->DBDDB->SurvivorItemDB.Get();
	if (LoadedObject)
	{
		ItemDataTable = Cast<UDataTable>(LoadedObject);
	}

}
