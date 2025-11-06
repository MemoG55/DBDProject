// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/AddonIcon.h"

#include "Components/Image.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/Item/SurvivorItem.h"
#include "JMS/ItemAddon/ItemAddonComponent.h"
#include "Shared/DBDStruct.h"
#include "Shared/DataAsset/DBDDataBase.h"
#include "Shared/GameFramework/DBDGameInstance.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/UI/DBDWidgetComponent.h"


void UAddonIcon::SetAddOnImage(FItemAddonData AddonData)
{
	IconImage->SetBrushFromSoftTexture(AddonData.Icon);
	SetIconLevel(AddonData.Tier);
	SetVisibility(ESlateVisibility::Visible);
}

void UAddonIcon::ClearAddonImage()
{
	IconImage->SetBrushFromSoftTexture(NULL);
	SetVisibility(ESlateVisibility::Collapsed);
}

void UAddonIcon::NativeConstruct()
{
	Super::NativeConstruct();
	ADBDPlayerState* DBDPS = Cast<ADBDPlayerState>(GetOwningPlayerState());
	UDBDGameInstance* DBDGI = Cast<UDBDGameInstance>(GetGameInstance());
	if (DBDPS && DBDGI)
	{
		CachedDBDDataBase = DBDGI->DBDDB;
		if (DBDPS->GetPlayerRole() == EPlayerRole::Killer)
		{
			ClearAddonImage();
		}
		else
		{
			const FItemAddonData* AddonData = CachedDBDDataBase->ItemAddonDB->FindRow<FItemAddonData>(
				DBDPS->SurvivorLoadout.ItemAddons[AddonIndex], "");
			if (AddonData)
			{
				SetAddOnImage(*AddonData);
			}
			else
			{
				ClearAddonImage();
			}
			if (ASurvivorCharacter* Survivor = GetOwningPlayerPawn<ASurvivorCharacter>())
			{
				Survivor->GetWidgetComponent()->OnUpdateEquippedItem.AddDynamic(
					this, &UAddonIcon::OnEquippedItemChanged);
			}
		}
	}
}

void UAddonIcon::OnEquippedItemChanged(ASurvivorItem* NewItem)
{
	if (ASurvivorCharacter* OwnerSurvivor = GetOwningPlayerPawn<ASurvivorCharacter>())
	{
		if (NewItem)
		{
			if (AddonIndex == 0)
			{
				if (NewItem->GetAddon1())
				{
					const FItemAddonData* AddonData = CachedDBDDataBase->ItemAddonDB->FindRow<FItemAddonData>(
						NewItem->GetAddon1()->GetAddonID(), "");
					if (AddonData)
					{
						SetAddOnImage(*AddonData);
					}
				}
				else
				{
					ClearAddonImage();
				}
			}
			else if (AddonIndex == 1)
			{
				if (NewItem->GetAddon2())
				{
					const FItemAddonData* AddonData = CachedDBDDataBase->ItemAddonDB->FindRow<FItemAddonData>(
						NewItem->GetAddon2()->GetAddonID(), "");
					if (AddonData)
					{
						SetAddOnImage(*AddonData);
					}
				}
				else
				{
					ClearAddonImage();
				}
			}
			else
			{
				ClearAddonImage();
			}
		}
		else
		{
			ClearAddonImage();
		}
		
	}
}
