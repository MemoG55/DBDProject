// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/DBDHUD.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Shared/UI/AbilityProgressWidget.h"
#include "MMJ/Object/GAS/ObjAttributeSet.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDEnum.h"
#include "Shared/DBDStruct.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/GameFramework/DBDGameStateBase.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/GAS/DBDAbilitySystemComponent.h"
#include "Shared/Perk/PerkComponent.h"
#include "Shared/UI/BasePerkIcon.h"
#include "MMJ/Object/Widget/Obj_Progress.h"
#include "Shared/UI/AbilityNameOnlyWidget.h"
#include "Shared/UI/EscapeTimerUI.h"
#include "Shared/UI/GeneratorIcon.h"
#include "Shared/UI/PerkUIHUD.h"


void UDBDHUD::InitializePerkWidget()
{
	// JMS: UI수정: Perk 정보는 아이콘이 개별로 찾도록 하겟습니다.
	// if (Character->GetInteractorRole() == PlayerRole)
	// {
	// 	//Debug::Print(TEXT("UDBDHUD::SetPerkUIHUD"), 341);
	// 	if (ADBDCharacter* HUDOwningCharacter = Character)
	// 	{
	// 		TArray<FName> PerkComponents;
	//
	// 		ADBDPlayerState* PlayerState = Cast<ADBDPlayerState>(Character->GetPlayerState());
	//
	// 		//YHG : �외처리 추�
	// 		if (!PlayerState)
	// 		{
	// 			//Debug::Print(TEXT("UDBDHUD::Cast Failed PlayerState!"), 342);
	// 			return;
	// 		}
	//
	// 		if (PlayerState->GetPlayerRole() == EPlayerRole::Killer)
	// 		{
	// 			FKillerLoadout KillerLoadout = PlayerState->KillerLoadout;
	// 			PerkComponents.Add(KillerLoadout.Perk1);
	// 			PerkComponents.Add(KillerLoadout.Perk2);
	// 			PerkComponents.Add(KillerLoadout.Perk3);
	// 			PerkComponents.Add(KillerLoadout.Perk4);
	// 		}
	// 		else
	// 		{
	// 			FSurvivorLoadout SurvivorLoadout = PlayerState->SurvivorLoadout;
	// 			PerkComponents.Add(SurvivorLoadout.Perk1);
	// 			PerkComponents.Add(SurvivorLoadout.Perk2);
	// 			PerkComponents.Add(SurvivorLoadout.Perk3);
	// 			PerkComponents.Add(SurvivorLoadout.Perk4);
	// 		}
	// 	
	// 		int32 index = 0;
	// 		for (FName PerkName : PerkComponents)
	// 		{
	// 			//Debug::Print(
	// 			//	FString::Printf(TEXT("UDBDHUD::SetPerkUIHUD:: Index: %d, %s"), index, *PerkName.ToString()), 350);
	// 			UPerkComponent* Perk = HUDOwningCharacter->GetAllPerks()[index];
	// 			const FPerkData* PerkStruct = PerkDataTable->FindRow<FPerkData>(PerkName, "");
	// 			if (PerkStruct == nullptr || PerkStruct->DisplayName.IsEmpty())
	// 			{
	// 				//Debug::Print(TEXT("UDBDHUD::SetPerkUIHUD:: Perk *NOT* Valid"), 346);
	// 				PerkUIHUD->PerkIcons[index]->SetIconVisible(ESlateVisibility::Hidden);
	// 				PerkUIHUD->PerkIcons[index]->StackText->SetVisibility(ESlateVisibility::Hidden);
	// 			}
	// 			else
	// 			{
	// 				//Debug::Print(TEXT("UDBDHUD::SetPerkUIHUD:: Struct Valid"), 345);
	// 				//Debug::Print(FString::Printf(
	// 				//	             TEXT("UDBDHUD::SetPerkUIHUD:: Struct Valid: %s"),
	// 				//	             *PerkStruct->DisplayName.ToString()), 347);
	// 				PerkUIHUD->SetPerksToHUD(index, *PerkStruct);
	// 				PerkUIHUD->PerkIcons[index]->SetIconVisible(ESlateVisibility::Visible);
	// 				if (!PerkStruct->IsStackable)
	// 					PerkUIHUD->PerkIcons[index]->StackText->SetVisibility(
	// 						ESlateVisibility::Hidden);
	// 			}
	// 			index++;
	// 		}
	// 	}
	// 	}
	// }
	
	
}

void UDBDHUD::SetProgressHUD(UDBDAbilitySystemComponent* ASC)
{
	if (!IsValid(ProgressHUD)) return;

	if (IsValid(ASC))
	{
		ProgressHUD->SetObjectASC(ASC, UObjAttributeSet::GetCurrentTaskAttribute(),
		                          UObjAttributeSet::GetMaxTaskAttribute());
		ProgressHUD->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ProgressHUD->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UDBDHUD::SetEndGameHUD()
{
	if (IsValid(EndGameHUD) && !EndGameHUD->IsVisible())
	{
		EndGameHUD->SetVisibility(ESlateVisibility::Visible);
	}
}

void UDBDHUD::SetLeftGeneratorIcon_Implementation(int32 Left)
{
	if (LeftGeneratorIcon)
	{
		LeftGeneratorIcon->SetGeneratorImage(Left);
	}
}

UEscapeTimerUI* UDBDHUD::GetEndGameHUD()
{
	return EndGameHUD.Get();
}

UGeneratorIcon* UDBDHUD::GetLeftGeneratorIcon()
{
	return LeftGeneratorIcon.Get();
}

void UDBDHUD::UpdateEndGameHUD(float NewValue)
{
	if (IsValid(EndGameHUD))
	{
		EndGameHUD->UpdateCurrentValue(NewValue);
	}
}

void UDBDHUD::NativeConstruct()
{
	Super::NativeConstruct();
	// JMS: UI수정: WidgetComponent에서 AddToViewport
	// if (!this->IsInViewport())
	// {
	// 	this->AddToViewport();
	// }
	ProgressHUD->SetVisibility(ESlateVisibility::Collapsed);
	EndGameHUD->SetVisibility(ESlateVisibility::Collapsed);
	AbilityProgressWidget->SetVisibility(ESlateVisibility::Collapsed);
	AbilityNameOnlyWidget->SetVisibility(ESlateVisibility::Collapsed);
	//AddToViewport();
}

void UDBDHUD::SetAddons(ADBDCharacter* Character)
{
}

void UDBDHUD::SetItemHUD(ADBDCharacter* Character)
{
	//구현� �식�서
}

void UDBDHUD::UpdateAbilityWidget(bool bIsVisible, FText Description, float Percentage)
{
	if (IsValid(AbilityProgressWidget))
	{
		AbilityProgressWidget->OnUpdate(bIsVisible, Description, Percentage);
	}
}

void UDBDHUD::UpdateAbilityNameOnlyWidget(bool bIsVisible, FText Description)
{
	if (IsValid(AbilityNameOnlyWidget))
	{
		AbilityNameOnlyWidget->OnSetVisibilityAndText(bIsVisible, Description);
	}
}
