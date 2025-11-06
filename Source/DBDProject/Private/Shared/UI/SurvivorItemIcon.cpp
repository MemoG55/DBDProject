// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/SurvivorItemIcon.h"

#include "Components/Image.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/GAS/SurvivorAttributeSet.h"
#include "JMS/Item/SurvivorItem.h"
#include "JMS/UI/SurvivorHUD.h"
#include "KMJ/AbilitySystem/HuntressAttributeSet.h"
#include "Shared/DataAsset/DBDDataBase.h"
#include "Shared/GameFramework/DBDGameInstance.h"
#include "Shared/UI/DBDWidgetComponent.h"


void USurvivorItemIcon::SetItemGaugeImageMaterialGaugeStat(const FOnAttributeChangeData& OnAttributeChangeData)
{
	float MaxItemCharge = 10.f;
	float CurrentItemCharge = OnAttributeChangeData.NewValue;
	if (OwnerSurvivor)
	{
		MaxItemCharge = OwnerSurvivor->GetAbilitySystemComponent()->GetNumericAttribute(
			USurvivorAttributeSet::GetMaxItemChargeAttribute());
	}
	if (ItemGaugeMaterialInstanceDynamic && !FMath::IsNearlyZero(MaxItemCharge))
	{
		ItemGaugeMaterialInstanceDynamic->SetScalarParameterValue(FName("CoolDownRemainingPercent"),
		                                                          CurrentItemCharge / MaxItemCharge);
	}
}

void USurvivorItemIcon::NativeConstruct()
{
	Super::NativeConstruct();
	APawn* OwningPlayerPawn = GetOwningPlayerPawn();
	if (UDBDGameInstance* DBDGI = Cast<UDBDGameInstance>(GetGameInstance()))
	{
		CachedDBDDataBase = DBDGI->DBDDB;
	}

	if (ItemGaugeImage && ItemGaugeImage->GetDynamicMaterial() == nullptr && TopDownItemGaugeMaterialInstance)
	{
		// 동적 머티리얼 생성
		ItemGaugeMaterialInstanceDynamic = UMaterialInstanceDynamic::Create(TopDownItemGaugeMaterialInstance, this);

		// UI 이미지에 적용
		ItemGaugeImage->SetBrushFromMaterial(ItemGaugeMaterialInstanceDynamic);
	}
	OwnerSurvivor = Cast<ASurvivorCharacter>(OwningPlayerPawn);
	if (OwnerSurvivor)
	{
		OwnerSurvivor->GetWidgetComponent()->OnUpdateEquippedItem.AddDynamic(
			this, &USurvivorItemIcon::OnEquippedItemChanged);
		OnEquippedItemChanged(OwnerSurvivor->GetEquippedItem());
	}
}

void USurvivorItemIcon::InitializeWithItemData(const FItemData& ItemData)
{
	// 초기화
	if (ItemGaugeMaterialInstanceDynamic && OwnerSurvivor)
	{
		float CurrentItemCharge = OwnerSurvivor->GetAbilitySystemComponent()->GetNumericAttribute(
			USurvivorAttributeSet::GetCurrentItemChargeAttribute());
		float MaxItemCharge = OwnerSurvivor->GetAbilitySystemComponent()->GetNumericAttribute(
			USurvivorAttributeSet::GetMaxItemChargeAttribute());
		if (!FMath::IsNearlyZero(MaxItemCharge))
		{
			ItemGaugeMaterialInstanceDynamic->SetScalarParameterValue(FName("CoolDownRemainingPercent"),
			                                                          CurrentItemCharge / MaxItemCharge);
		}
	}
	SetVisibility(ESlateVisibility::Visible);
	SetIcon(ItemData.Icon);
	SetIconLevel(ItemData.Tier);
	EffectImage->SetVisibility(ESlateVisibility::Collapsed);
	if (OwnerSurvivor)
	{
		// 바인딩
		OwnerSurvivor->GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(
			USurvivorAttributeSet::GetCurrentItemChargeAttribute()).AddUObject(
			this, &USurvivorItemIcon::SetItemGaugeImageMaterialGaugeStat);
	}
}

void USurvivorItemIcon::OnEquippedItemChanged(ASurvivorItem* NewItem)
{
	if (OwnerSurvivor)
	{
		FName ItemName = NewItem ? NewItem->GetItemID() : NAME_None;
		const FItemData* ItemData = CachedDBDDataBase->SurvivorItemDB->FindRow<FItemData>(
			ItemName, TEXT("USurvivorHUD::SetItemHUD"));
		if (!ItemData)
		{
			SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			InitializeWithItemData(*ItemData);
		}
	}
}
