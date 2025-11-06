// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/PerkUIHUD.h"

#include "Components/TextBlock.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "Shared/UI/BasePerkIcon.h"

void UPerkUIHUD::SetPerksToHUD(int index, FPerkData PerkStruct)
{
	// JMS: UI수정: 아이콘이 퍽 정보 갖도록 하겠습니다...
	
	// if (!PerkStruct.Icon.IsNull())
	// {
	// 	//UE_LOG(LogTemp, Display, TEXT("Icon Address:: %s"), PerkStruct.Icon);
	// 	UE_LOG(LogTemp, Display, TEXT("Icon Name:: %s"), *PerkStruct.Icon.GetAssetName());
	// }
	// PerkIcons[index]->SetIcon(PerkStruct.Icon);
	// PerkIcons[index]->SetIconLevel(PerkStruct.Tier);
	// if (PerkStruct.IsStackable)
	// {
	// 	PerkIcons[index]->SetStackText(PerkStruct.Stack);
	// 	PerkIcons[index]->StackText->SetVisibility(ESlateVisibility::Visible);
	// }
	// else
	// 	PerkIcons[index]->StackText->SetVisibility(ESlateVisibility::Hidden);
}

void UPerkUIHUD::NativeConstruct()
{
	Super::NativeConstruct();
	// JMS: UI수정: 아이콘이 퍽 정보 갖도록 하겠습니다...
	
	// PerkIcons.Add(PerkIcon1);
	// PerkIcons.Add(PerkIcon2);
	// PerkIcons.Add(PerkIcon3);
	// PerkIcons.Add(PerkIcon4);
	// if (PerkIcons.Num() > 0)
	// {
	// 	for (UBasePerkIcon* perkIcon : PerkIcons)
	// 	{
	// 		if (!perkIcon)
	// 			perkIcon->SetVisibility(ESlateVisibility::Hidden);
	// 		else
	// 			perkIcon->SetVisibility(ESlateVisibility::Visible);
	// 	}
	// }
}
