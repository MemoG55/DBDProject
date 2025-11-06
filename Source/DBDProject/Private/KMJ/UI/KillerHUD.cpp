// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/UI/KillerHUD.h"

#include "AbilitySystemComponent.h"
#include "KMJ/Character/KillerHuntress.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/UI/AddonIcon.h"
#include "GameplayTagsManager.h"
#include "Components/TextBlock.h"
#include "KMJ/AbilitySystem/KillerAttributeSet.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/UI/KillerSkillHUD.h"
#include "Shared/UI/KillerSkillIcon.h"



void UKillerHUD::SetCarryingUI()
{
	//UI 애니메이션 추가해야 함
	KillerSkillHUD->SetVisibility(ESlateVisibility::Hidden);

	CarriedSurvivorIcon->SetVisibility(ESlateVisibility::Visible);
	CarryingKillerSkillHUD->SetVisibility(ESlateVisibility::Visible);
}

void UKillerHUD::SetOffCarryingKillerUI()
{
	//UI 애니메이션 추가해야 함
	CarriedSurvivorIcon->SetVisibility(ESlateVisibility::Hidden);
	CarryingKillerSkillHUD->SetVisibility(ESlateVisibility::Hidden);
	
	KillerSkillHUD->SetVisibility(ESlateVisibility::Visible);
}

// void UKillerHUD::SetItemHUD(ADBDCharacter* Character)
// {
// 	UE_LOG(LogTemp, Warning, TEXT("[Before Call] UKillerHUD::SetItemHUD:: KillerSkillHUD: %s"), IsValid(KillerSkillHUD) ? TEXT("VALID") : TEXT("NULL"));
// 	if (Character)
// 	{
// 		//if (!ensureMsgf(KillerSkillHUD, TEXT("KillerSkillHUD is null. Check WidgetBP binding.")))
// 			//return;
// 		if (Character->GetInteractorRole() == EPlayerRole::Killer)
// 		{
// 			if (KillerSkillHUD)
// 			{
// 				KillerSkillHUD->SetVisibility(ESlateVisibility::Visible);
// 				KillerSkillHUD->KillerSkillIcon->SetKillerSkillIcon(Cast<AKillerHuntress>(Character));
// 				CarryingKillerSkillHUD->KillerSkillIcon->SetKillerSkillIcon(Cast<AKillerHuntress>(Character));
// 				SetAddons(Character);
// 			}
// 		}
// 	}
// 	UE_LOG(LogTemp, Warning, TEXT("[After Call] UKillerHUD::SetItemHUD:: KillerSkillHUD: %s"), IsValid(KillerSkillHUD) ? TEXT("VALID") : TEXT("NULL"));
// }

void UKillerHUD::OnCarryingTagChanged(FGameplayTag GameplayTag, int i)
{
	if (i > 0)
	{
		// 태그가 추가됨
		SetCarryingUI();
	}
	else
	{
		// 태그가 제거됨
		SetOffCarryingKillerUI();
	}
}

void UKillerHUD::NativeConstruct()
{
	Super::NativeConstruct();
	AActor* Owner = GetOwningPlayerPawn();
	Huntress = Cast<AKillerHuntress>(Owner);
	if (!Owner) return;

	// ASC 얻기 (AbilitySystemInterface를 통해)
	if (IAbilitySystemInterface* AbilityInterface = Cast<IAbilitySystemInterface>(Owner))
	{
		UAbilitySystemComponent* ASC = AbilityInterface->GetAbilitySystemComponent();
		if (!ASC) return;

		// 감시할 태그
		const FGameplayTag CarryingTag = DBDGameplayTags::Killer_Common_Status_Carrying;
		
		// 델리게이트 바인딩
		ASC->RegisterGameplayTagEvent(CarryingTag, EGameplayTagEventType::NewOrRemoved)
			.AddUObject(this, &UKillerHUD::OnCarryingTagChanged);
	}

	if (!KillerSkillHUD)
	{
		//Debug::Print(TEXT("***UKillerHUD::NativeConstruct:: KillerSkillHUD is  NOT Valid"), 359);
	}
	else
	{
		//Debug::Print(TEXT("UKillerHUD::NativeConstruct:: KillerSkillHUD is VALID"), 359);
	}
	
	if (Huntress && Huntress->HuntressAttributeSet)
	{
		Huntress->KillerAttributeSet->OnWalkingSpeedChanged.AddDynamic(this, &UKillerHUD::OnWalkingSpeedChanged);
		SetKillerSkillIcon();
		WalkingSpeed->SetVisibility(ESlateVisibility::Visible);
	}
	SetOffCarryingKillerUI();
}

void UKillerHUD::OnWalkingSpeedChanged(float NewWalkingSpeed)
{
	if (WalkingSpeed)
		WalkingSpeed->SetText(FText::AsNumber(NewWalkingSpeed));
}

void UKillerHUD::SetKillerSkillIcon()
{
	if (WalkingSpeed)
		WalkingSpeed->SetText(FText::AsNumber(Huntress->KillerAttributeSet->GetWalkingSpeed()));
}

// void UKillerHUD::SetAddons(ADBDCharacter* Character)
// {
// 	if (Character)
// 	{
// 		TArray<FName> PerkComponents;
// 		ADBDPlayerState* PlayerState = Cast<ADBDPlayerState>(Character->GetPlayerState());
// 		if (PlayerState)
// 		{
// 			FName Addon1 = PlayerState->KillerLoadout.Addon1;
// 			FName Addon2 = PlayerState->KillerLoadout.Addon2;
// 			FItemAddonData* AddonData1 = PerkDataTable->FindRow<FItemAddonData>(Addon1, "");
// 			FItemAddonData* AddonData2 = PerkDataTable->FindRow<FItemAddonData>(Addon2, "");
//
// 			if (!AddonData1 && AddonData2)
// 			{
// 				KillerSkillHUD->SkillAddonIcon1->SetVisibility(ESlateVisibility::Hidden);
// 				KillerSkillHUD->SkillAddonIcon2->SetAddOnImage(*AddonData2);
// 				
// 				CarryingKillerSkillHUD->SkillAddonIcon1->SetVisibility(ESlateVisibility::Hidden);
// 				CarryingKillerSkillHUD->SkillAddonIcon2->SetAddOnImage(*AddonData2);
// 			}
// 			else if (!AddonData2 && AddonData1)
// 			{
// 				KillerSkillHUD->SkillAddonIcon2->SetVisibility(ESlateVisibility::Visible);
// 				KillerSkillHUD->SkillAddonIcon1->SetAddOnImage(*AddonData1);
//
// 				CarryingKillerSkillHUD->SkillAddonIcon2->SetVisibility(ESlateVisibility::Hidden);
// 				CarryingKillerSkillHUD->SkillAddonIcon1->SetAddOnImage(*AddonData2);
// 			}
// 			else if (AddonData1 && AddonData2)
// 			{
// 				KillerSkillHUD->SetAddonIcons(*AddonData1, *AddonData2);
// 				CarryingKillerSkillHUD->SetAddonIcons(*AddonData1, *AddonData2);
// 			}
// 			else
// 			{
// 				KillerSkillHUD->SkillAddonIcon1->SetVisibility(ESlateVisibility::Hidden);
// 				CarryingKillerSkillHUD->SkillAddonIcon1->SetVisibility(ESlateVisibility::Hidden);
// 				KillerSkillHUD->SkillAddonIcon2->SetVisibility(ESlateVisibility::Hidden);
// 				CarryingKillerSkillHUD->SkillAddonIcon2->SetVisibility(ESlateVisibility::Hidden);
// 			}
// 		}
// 	}
// }