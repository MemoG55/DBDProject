// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/BasePerkIcon.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Shared/DBDEnum.h"
#include "Shared/DataAsset/DBDDataBase.h"
#include "Shared/GameFramework/DBDGameInstance.h"
#include "Shared/GameFramework/DBDPlayerState.h"


void UBasePerkIcon::SetStackText(int InputStack)
{
	if (StackText)
	{
		StackText->SetVisibility(ESlateVisibility::Visible);
		StackText->SetText(FText::AsNumber(InputStack));
	}
}

void UBasePerkIcon::SetIconLevel(ETier Tier)
{
	if (IconLevelImage)
	{
		LevelImage1->SetVisibility(ESlateVisibility::Visible);
		LevelImage2->SetVisibility(ESlateVisibility::Visible);
		LevelImage3->SetVisibility(ESlateVisibility::Visible);
		if (Tier == ETier::Green)
		{
			//Green
			LevelImage3->SetVisibility(ESlateVisibility::Hidden);
			IconLevelImage->SetColorAndOpacity(FLinearColor(0.0275f, 0.25098f, 0.06275f, 1.0f));
		}
		else if (Tier == ETier::Yellow)
		{
			//Yellow
			LevelImage2->SetVisibility(ESlateVisibility::Hidden);
			LevelImage3->SetVisibility(ESlateVisibility::Hidden);
			IconLevelImage->SetColorAndOpacity(FLinearColor(0.75686f, 0.63922f, 0.28627f, 1.0f));
		}
		else
		{
			//Purple
			FColor sRGBColor(134, 97, 149, 255);
			IconLevelImage->SetColorAndOpacity(FLinearColor::FromSRGBColor(sRGBColor));
		}
	}
}

void UBasePerkIcon::SetIconVisible(ESlateVisibility IsVisible)
{
	LevelImage1->SetVisibility(IsVisible);
	LevelImage2->SetVisibility(IsVisible);
	LevelImage3->SetVisibility(IsVisible);
	Super::SetIconVisible(IsVisible);
}

void UBasePerkIcon::NativeConstruct()
{
	Super::NativeConstruct();
	// JMS: UI수정: 자신의 인덱스 번호에 맞는 퍽 아이콘 할당
	SetVisibility(ESlateVisibility::Visible);
	ADBDPlayerState* DBDPS = Cast<ADBDPlayerState>(GetOwningPlayerState());
	UDBDGameInstance* DBDGI = Cast<UDBDGameInstance>(GetGameInstance());
	if (DBDPS && DBDGI)
	{
		if (DBDPS->GetPlayerRole() == EPlayerRole::Killer)
		{
			const FPerkData* PerkStruct = DBDGI->DBDDB->KillerPerkDB->FindRow<FPerkData>(
				DBDPS->KillerLoadout.Perks[PerkIndex], "");
			if (PerkStruct == nullptr || PerkStruct->DisplayName.IsEmpty())
			{
				SetIconVisible(ESlateVisibility::Collapsed);
				StackText->SetVisibility(ESlateVisibility::Collapsed);
			}
			else
			{
				InitializePerkIcon(*PerkStruct);
			}
		}
		else
		{
			const FPerkData* PerkStruct = DBDGI->DBDDB->SurvivorPerkDB->FindRow<FPerkData>(
				DBDPS->SurvivorLoadout.Perks[PerkIndex], "");
			if (PerkStruct == nullptr || PerkStruct->DisplayName.IsEmpty())
			{
				SetIconVisible(ESlateVisibility::Collapsed);
				StackText->SetVisibility(ESlateVisibility::Collapsed);
			}
			else
			{
				InitializePerkIcon(*PerkStruct);
			}
		}
	}
}

void UBasePerkIcon::InitializePerkIcon(const FPerkData& PerkData)
{
	if (!PerkData.Icon.IsNull())
	{
		//UE_LOG(LogTemp, Display, TEXT("Icon Address:: %s"), PerkStruct.Icon);
		UE_LOG(LogTemp, Display, TEXT("Icon Name:: %s"), *PerkData.Icon.GetAssetName());
	}
	SetIcon(PerkData.Icon);
	SetIconLevel(PerkData.Tier);
	SetIconVisible(ESlateVisibility::Visible);
	if (PerkData.IsStackable)
	{
		SetStackText(PerkData.Stack);
		StackText->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		StackText->SetVisibility(ESlateVisibility::Hidden);
	}
}
