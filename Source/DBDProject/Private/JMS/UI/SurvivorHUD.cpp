// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/UI/SurvivorHUD.h"

#include "Components/Image.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/GAS/ItemAttributeSet.h"
#include "JMS/GAS/SurvivorAttributeSet.h"
#include "JMS/Item/SurvivorItem.h"
#include "JMS/ItemAddon/ItemAddonComponent.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/UI/AddonIcon.h"
#include "Shared/UI/SurvivorItemHUD.h"
#include "Shared/UI/SurvivorItemIcon.h"


void USurvivorHUD::NativeConstruct()
{
	Super::NativeConstruct();
}
//
// void USurvivorHUD::SetAddons(ADBDCharacter* Character)
// {
// 	 ASurvivorCharacter* Survivor = Cast<ASurvivorCharacter>(Character);
// 	 if (!IsValid(SurvivorItemHUD))
// 	 {
// 	 	UE_LOG(LogTemp, Warning, TEXT("SetAddons: SurvivorItemHUD is null"));
// 	 	return;
// 	 }
// 	 if (!IsValid(PerkDataTable))
// 	 {
// 	 	UE_LOG(LogTemp, Warning, TEXT("SetAddons: PerkDataTable is null"));
// 	 	SurvivorItemHUD->AddonIcon1->SetVisibility(ESlateVisibility::Collapsed);
// 	 	SurvivorItemHUD->AddonIcon2->SetVisibility(ESlateVisibility::Collapsed);
// 	 	return;
// 	 }
// 	
// 	 if (!IsValid(Survivor)) return;
// 	
// 	 ASurvivorItem* Item = Survivor->GetEquippedItem();
// 	
// 	 if (!IsValid(Item))
// 	 {
// 	 	SurvivorItemHUD->AddonIcon1->SetVisibility(ESlateVisibility::Collapsed);
// 	 	SurvivorItemHUD->AddonIcon2->SetVisibility(ESlateVisibility::Collapsed);
// 	 	SurvivorItemHUD->SetVisibility(ESlateVisibility::Collapsed);
// 	 	return;
// 	 }
// 	
// 	 if (!IsValid(ItemTable))
// 	 {
// 	 	UE_LOG(LogTemp, Warning, TEXT("SetItemHUD: ItemTable is null"));
// 	 	return;
// 	 }
// 	
// 	 const FName ItemName = Item->GetItemID();
// 	 const FItemData* ItemData = ItemTable->FindRow<FItemData>(ItemName, TEXT("USurvivorHUD::SetItemHUD"));
// 	 if (!ItemData)
// 	 {
// 	 	ClearItemIcon();
// 	 	return;
// 	 }
//
// 	 if (Survivor->GetSurvivorAttributeSet()->OnCurrentItemChargeChanged.IsBound())
// 	 	Survivor->GetSurvivorAttributeSet()->OnCurrentItemChargeChanged.Unbind();
// 	 Survivor->GetSurvivorAttributeSet()->OnCurrentItemChargeChanged.BindDynamic(
// 	 	SurvivorItemHUD->SurvivorIcon, &USurvivorItemIcon::SetItemGaugeImageMaterialGaugeStat);
// 	 Survivor->GetSurvivorAttributeSet()->OnCurrentItemChargeChanged.ExecuteIfBound(
// 	 	Survivor->GetSurvivorAttributeSet()->GetCurrentItemCharge() / Survivor->GetSurvivorAttributeSet()->
// 	 	GetMaxItemCharge());
//
// 	
// 	 // 정상 세팅
// 	 SurvivorItemHUD->SetVisibility(ESlateVisibility::Visible);
// 	 if (IsValid(SurvivorItemHUD->SurvivorIcon))
// 	 {
// 	 	// JMS: SurvivorItemIcon초기화
// 	 	SurvivorItemHUD->SurvivorIcon->InitializeWithItemData(*ItemData);
// 	 }
//
// 	 // 애드온 컴포넌트/ID 가드
// 	 UItemAddonComponent* AddonComp1 = Item->GetAddon1();
// 	 UItemAddonComponent* AddonComp2 = Item->GetAddon2();
// 	 // JMS: NULL체크
// 	 const FName Addon1 = AddonComp1 ? AddonComp1->GetAddonID() : FName(TEXT("NAME_None"));
// 	 const FName Addon2 = AddonComp2 ? AddonComp2->GetAddonID() : FName(TEXT("NAME_None"));
// 	
// 	 const FItemAddonData* AddonData1 = (Addon1 != NAME_None)
// 	 	                                   ? AddonTable->FindRow<FItemAddonData>(
// 	 		                                   Addon1, TEXT("USurvivorHUD::SetAddons"))
// 	 	                                   : nullptr;
// 	 const FItemAddonData* AddonData2 = (Addon2 != NAME_None)
// 	 	                                   ? AddonTable->FindRow<FItemAddonData>(
// 	 		                                   Addon2, TEXT("USurvivorHUD::SetAddons"))
// 	 	                                   : nullptr;
// 	
// 	 // 케이스별 처리 (else-if 사다리)
// 	 if (AddonData1 && AddonData2)
// 	 {
// 	 	SurvivorItemHUD->AddonIcon1->SetVisibility(ESlateVisibility::Visible);
// 	 	SurvivorItemHUD->AddonIcon2->SetVisibility(ESlateVisibility::Visible);
// 	 	SurvivorItemHUD->SetAddonIcons(*AddonData1, *AddonData2);
// 	 }
// 	 else if (AddonData1 && !AddonData2)
// 	 {
// 	 	SurvivorItemHUD->AddonIcon1->SetVisibility(ESlateVisibility::Visible);
// 	 	SurvivorItemHUD->AddonIcon2->SetVisibility(ESlateVisibility::Hidden);
// 	 	SurvivorItemHUD->AddonIcon1->SetAddOnImage(*AddonData1);
// 	 }
// 	 else if (!AddonData1 && AddonData2)
// 	 {
// 	 	SurvivorItemHUD->AddonIcon1->SetVisibility(ESlateVisibility::Hidden);
// 	 	SurvivorItemHUD->AddonIcon2->SetVisibility(ESlateVisibility::Visible);
// 	 	SurvivorItemHUD->AddonIcon2->SetAddOnImage(*AddonData2);
// 	 }
// 	 else
// 	 {
// 	 	SurvivorItemHUD->AddonIcon1->SetVisibility(ESlateVisibility::Hidden);
// 	 	SurvivorItemHUD->AddonIcon2->SetVisibility(ESlateVisibility::Hidden);
// 	 }
// }
//
// void USurvivorHUD::SetItemHUD(ADBDCharacter* Character)
// {
// 	if (Character && Character->GetInteractorRole() == EPlayerRole::Survivor)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("[Before Call] USurvivorHUD::SetItemHUD:: SurvivorItemHUD: %s"),
// 		       IsValid(SurvivorItemHUD) ? TEXT("VALID") : TEXT("NULL"));
// 	
// 	
// 		if (!IsValid(SurvivorItemHUD))
// 			return;
// 	
// 		ASurvivorCharacter* Survivor = Cast<ASurvivorCharacter>(Character);
// 		//Survivor->EquippedItemChangedDelegate.AddDynamic(this, &USurvivorHUD::SetItemNAddonIcon);
// 		if (IsValid(Survivor))
// 			SetAddons(Survivor);
// 	
// 	
// 		UE_LOG(LogTemp, Warning, TEXT("[After Call] USurvivorHUD::SetItemHUD:: SurvivorItemHUD: %s"),
// 		       IsValid(SurvivorItemHUD) ? TEXT("VALID") : TEXT("NULL"));
// 	}
// }
//
// void USurvivorHUD::ClearItemIcon()
// {
// 	SurvivorItemHUD->SetVisibility(ESlateVisibility::Hidden);
// 	OnCurrentItemChargeChanged 미사용
// 	ASurvivorCharacter* Survivor = Cast<ASurvivorCharacter>(GetOwningPlayerPawn());
// 	if (Survivor->GetSurvivorAttributeSet()->OnCurrentItemChargeChanged.IsBound())
// 		Survivor->GetSurvivorAttributeSet()->OnCurrentItemChargeChanged.Unbind();
// }
