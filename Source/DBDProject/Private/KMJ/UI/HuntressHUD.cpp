// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/UI/HuntressHUD.h"

#include <string>

#include "Components/TextBlock.h"
#include "KMJ/AbilitySystem/HuntressAttributeSet.h"
#include "KMJ/Character/KillerHuntress.h"
#include "Shared/GameFramework/DBDPlayerState.h"


UHuntressHUD::UHuntressHUD()
{
	//CurrentAxeNum = CreateDefaultSubobject<UTextBlock>(TEXT("CurrentAxeNum"));
}

void UHuntressHUD::OnAxeNumberChanged(float NewAxeNumber)
{
	if (CurrentAxeNum)
		CurrentAxeNum->SetText(FText::AsNumber(NewAxeNumber));
}

void UHuntressHUD::OnWalkingSpeedChanged(float NewWalkingSpeed)
{
	if (WalkingSpeed)
		WalkingSpeed->SetText(FText::AsNumber(NewWalkingSpeed));
}

void UHuntressHUD::NativeConstruct()
{
	Super::NativeConstruct();
	Huntress =  Cast<AKillerHuntress>(GetOwningPlayerPawn()) ? Cast<AKillerHuntress>(GetOwningPlayerPawn()) : nullptr;
	// Listen to the AxeNumber change delegate
	if (Huntress && Huntress->HuntressAttributeSet)
	{
		Huntress->HuntressAttributeSet->OnAxeNumberChanged.AddDynamic(this, &UHuntressHUD::OnAxeNumberChanged);
		Huntress->KillerAttributeSet->OnWalkingSpeedChanged.AddDynamic(this, &UHuntressHUD::OnWalkingSpeedChanged);
	}
	if (CurrentAxeNum)
		CurrentAxeNum->SetText(FText::AsNumber(Huntress->HuntressAttributeSet->GetAxeNumber()));
	if (WalkingSpeed)
		WalkingSpeed->SetText(FText::AsNumber(Huntress->KillerAttributeSet->GetWalkingSpeed()));
}
