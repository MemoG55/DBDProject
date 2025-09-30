// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/UI/SurvivorItemSlot.h"

#include "Components/Image.h"
#include "Engine/AssetManager.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/Item/SurvivorItem.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DataAsset/DBDDataBase.h"
#include "Shared/GameFramework/DBDGameInstance.h"
#include "Shared/GameFramework/DBDPlayerState.h"


void USurvivorItemSlot::NativeConstruct()
{
	Super::NativeConstruct();
	CachedSurvivorCharacter = Cast<ASurvivorCharacter>(GetOwningPlayerPawn());
	if (CachedSurvivorCharacter)
	{
		CachedSurvivorCharacter->EquippedItemChangedDelegate.AddDynamic(this,&USurvivorItemSlot::OnItemChanged);
	}
	CachedGI = GetGameInstance<UDBDGameInstance>();
}

void USurvivorItemSlot::OnLoadoutChanged(FSurvivorLoadout Loadout)
{
}

void USurvivorItemSlot::OnItemChanged(ASurvivorItem* EquippedItem)
{
	CachedItem = EquippedItem;
	FSoftObjectPath AssetPath = CachedGI->DBDDB->SurvivorItemDB.ToSoftObjectPath();
	if (!CachedItem)
	{
		ItemIcon->SetBrushTintColor(FSlateColor(FLinearColor::Transparent));
		return;
	}
	if (AssetPath.IsValid())
	{
		UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
			AssetPath, FStreamableDelegate::CreateLambda([this]()
			{
				UObject* LoadedObject = CachedGI->DBDDB->SurvivorItemDB.Get();
				if (LoadedObject)
				{
					UDataTable* DT = Cast<UDataTable>(LoadedObject);
					if (!CachedItem)
					{
						Debug::Print(TEXT("JMS14 : SurvivorItemSlot : OnItemChanged : Item is null"), 14);
						return;
					}
					if (DT)
					{
						if (!CachedItem->GetItemID().IsValid())
						{
							Debug::Print(TEXT("JMS15 : SurvivorItemSlot : OnItemChanged : Item->GetItemID() is Invalid"), 15);
							
							return;
						}
						FItemData* ItemData = DT->FindRow<FItemData>(CachedItem->GetItemID(), "");
						if (ItemData)
						{
							ItemIcon->SetBrushTintColor(FSlateColor(FLinearColor::White));
							ItemIcon->SetBrushFromSoftTexture(ItemData->Icon);
						}
					}
				}
			}));
	}
}
