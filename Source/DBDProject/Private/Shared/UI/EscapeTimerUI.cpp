// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/EscapeTimerUI.h"

#include "Components/ProgressBar.h"
#include "Shared/GameFramework/DBDGameStateBase.h"


void UEscapeTimerUI::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);
	
	if (ADBDGameStateBase* GS = Cast<ADBDGameStateBase>(GetWorld()->GetGameState()))
	{
		MaxEscapeTime = GS->GetMaxEscapeTime();
		GS->OnEscapeTimerBegin.AddDynamic(this, &ThisClass::SetDisplay);
		GS->OnEscapeTimer.AddDynamic(this, &ThisClass::Update);
	}
}

void UEscapeTimerUI::SetDisplay()
{
	SetVisibility(ESlateVisibility::Visible);
}


void UEscapeTimerUI::Update(float NewValue)
{
	if (ProgressBar && MaxEscapeTime > 0)
	{
		ProgressBar->SetPercent(NewValue / MaxEscapeTime);
	}
}
