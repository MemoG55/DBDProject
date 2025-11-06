// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/EscapeTimerUI.h"

#include "Components/ProgressBar.h"
#include "Shared/Subsystem/DBDEndGameSubsystem.h"


UEscapeTimerUI::UEscapeTimerUI()
{
}

void UEscapeTimerUI::ChangeProgressBar(bool bIsSlow)
{
	FProgressBarStyle CurrentStyle = ProgressBar->GetWidgetStyle();
	
	FSlateBrush NewBackgroundBrush;
	NewBackgroundBrush.DrawAs = ESlateBrushDrawType::Type::Box;
	FSlateBrush NewFillBrush;
	NewFillBrush.DrawAs = ESlateBrushDrawType::Type::Box;
	
	if (bIsSlow)
	{
		NewBackgroundBrush.SetResourceObject(SlowProgressBackground);
		NewFillBrush.SetResourceObject(SlowProgressFill);
	}
	else
	{
		NewBackgroundBrush.SetResourceObject(BaseProgressBackground);
		NewFillBrush.SetResourceObject(BaseProgressFill);
	}
	CurrentStyle.BackgroundImage = NewBackgroundBrush;
	CurrentStyle.FillImage = NewFillBrush;

	ProgressBar->SetWidgetStyle(CurrentStyle);
}

void UEscapeTimerUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (UDBDEndGameSubsystem* GS = GetWorld()->GetSubsystem<UDBDEndGameSubsystem>())
	{
		UpdateMaxValue(GS->EscapeDuration);
	}
}

void UEscapeTimerUI::Update()
{	
	Super::Update();
}
