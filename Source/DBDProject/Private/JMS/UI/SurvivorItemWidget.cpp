// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/UI/SurvivorItemWidget.h"

#include "Components/Image.h"
#include "Components/ListView.h"
#include "Components/SizeBox.h"
#include "Engine/AssetManager.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/Item/SurvivorItem.h"
#include "JMS/ItemAddon/ItemAddonComponent.h"
#include "JMS/UI/ItemAddonSlot.h"
#include "JMS/UI/ItemSlot.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DataAsset/DBDDataBase.h"
#include "Shared/GameFramework/DBDGameInstance.h"
#include "Shared/GameFramework/DBDPlayerState.h"


void USurvivorItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CachedSurvivorCharacter = Cast<ASurvivorCharacter>(GetOwningPlayerPawn());
	// OnItemChanged(CachedSurvivorCharacter->GetEquippedItem());
	// if (CachedSurvivorCharacter)
	// {
	// 	CachedSurvivorCharacter->EquippedItemChangedDelegate.AddDynamic(this, &USurvivorItemWidget::OnItemChanged);
	// }
}

//
// void USurvivorItemWidget::OnItemChanged(ASurvivorItem* EquippedItem)
// {
// 	CachedItem = EquippedItem;
// 	if (!CachedItem)
// 	{
// 		ItemSlot->SetVisibility(ESlateVisibility::Collapsed);
// 		AddonSlot->SetVisibility(ESlateVisibility::Collapsed);
// 	}
// 	else
// 	{
// 		ItemSlot->SetVisibility(ESlateVisibility::Visible);
// 		AddonSlot->SetVisibility(ESlateVisibility::Visible);
// 	}
// }
