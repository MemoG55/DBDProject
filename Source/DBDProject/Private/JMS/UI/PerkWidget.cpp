// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/UI/PerkWidget.h"

#include "Components/Image.h"
#include "Engine/AssetManager.h"
#include "Shared/DBDEnum.h"
#include "Shared/DBDStruct.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/DataAsset/DBDDataBase.h"
#include "Shared/GameFramework/DBDGameInstance.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/Perk/PerkComponent.h"


void UPerkWidget::SetPerkIcon(UPerkComponent* NewPerk1, UPerkComponent* NewPerk2, UPerkComponent* NewPerk3,
                              UPerkComponent* NewPerk4)
{
	if (!PerkDataTable || (!NewPerk1 && !NewPerk2 && !NewPerk3 && !NewPerk4))
	{
		SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	if (NewPerk1&&Perk1Icon)
	{
		FPerkData* PerkData = PerkDataTable->FindRow<FPerkData>(NewPerk1->GetPerkID(), "");
		if (PerkData)
		{
			SetVisibility(ESlateVisibility::Visible);
			Perk1Icon->SetBrushFromSoftTexture(PerkData->Icon);
			Perk1Icon->SetDesiredSizeOverride(FVector2D(100.f, 100.f));
			Perk1Icon->SetBrushTintColor(FSlateColor(FLinearColor::White));
		}
	}
	if (NewPerk2&&Perk2Icon)
	{
		FPerkData* PerkData = PerkDataTable->FindRow<FPerkData>(NewPerk2->GetPerkID(), "");
		if (PerkData)
		{
			SetVisibility(ESlateVisibility::Visible);
			Perk2Icon->SetBrushFromSoftTexture(PerkData->Icon);
			Perk2Icon->SetDesiredSizeOverride(FVector2D(100.f, 100.f));
			Perk2Icon->SetBrushTintColor(FSlateColor(FLinearColor::White));
		}
	}
	if (NewPerk3&&Perk3Icon)
	{
		FPerkData* PerkData = PerkDataTable->FindRow<FPerkData>(NewPerk3->GetPerkID(), "");
		if (PerkData)
		{
			SetVisibility(ESlateVisibility::Visible);
			Perk3Icon->SetBrushFromSoftTexture(PerkData->Icon);
			Perk3Icon->SetDesiredSizeOverride(FVector2D(100.f, 100.f));
			Perk3Icon->SetBrushTintColor(FSlateColor(FLinearColor::White));
		}
	}
	if (NewPerk4&&Perk4Icon)
	{
		FPerkData* PerkData = PerkDataTable->FindRow<FPerkData>(NewPerk4->GetPerkID(), "");
		if (PerkData)
		{
			SetVisibility(ESlateVisibility::Visible);
			Perk4Icon->SetBrushFromSoftTexture(PerkData->Icon);
			Perk4Icon->SetDesiredSizeOverride(FVector2D(100.f, 100.f));
			Perk4Icon->SetBrushTintColor(FSlateColor(FLinearColor::White));
		}
	}
}

void UPerkWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UDBDGameInstance* GI = GetGameInstance<UDBDGameInstance>();
	if (!GI)
	{
		return;
	}
	FSoftObjectPath AssetPath = GI->DBDDB->SurvivorPerkDB.ToSoftObjectPath();

	if (AssetPath.IsValid())
	{
		UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
			AssetPath, FStreamableDelegate::CreateUObject(this, &UPerkWidget::OnDataTableLoaded));
	}
	ADBDCharacter* DBDCharacter = GetOwningPlayerPawn<ADBDCharacter>();
	if (DBDCharacter)
	{
		// DBDCharacter->OnPerkInfoInitializedOnClient.AddDynamic(this, &UPerkWidget::SetPerkIcon);
	}
}

void UPerkWidget::OnDataTableLoaded()
{
	UDBDGameInstance* GI = GetGameInstance<UDBDGameInstance>();
	if (!GI)
	{
		return;
	}
	ADBDPlayerState* DBDPlayerState = Cast<ADBDPlayerState>(GetOwningPlayerState());
	if (DBDPlayerState)
	{
		EPlayerRole PlayerRole = DBDPlayerState->GetPlayerRole();
		if (PlayerRole == EPlayerRole::Killer)
		{
			UObject* LoadedObject = GI->DBDDB->KillerPerkDB.Get();
			if (LoadedObject)
			{
				PerkDataTable = Cast<UDataTable>(LoadedObject);
			}
		}
		else
		{
			UObject* LoadedObject = GI->DBDDB->SurvivorPerkDB.Get();
			if (LoadedObject)
			{
				PerkDataTable = Cast<UDataTable>(LoadedObject);
			}
		}
	}
}
