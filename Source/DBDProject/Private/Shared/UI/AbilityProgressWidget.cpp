// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/AbilityProgressWidget.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/UI/DBDWidgetComponent.h"


void UAbilityProgressWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ADBDCharacter* OwningPlayerPawn = Cast<ADBDCharacter>(GetOwningPlayerPawn());
	if (OwningPlayerPawn)
	{
		OwningPlayerPawn->GetWidgetComponent()->OnUpdateAbilityProgress.AddDynamic(this, &UAbilityProgressWidget::OnUpdate);
	}
}

void UAbilityProgressWidget::OnUpdate(bool bIsVisible, FText Description, float Percentage)
{
	if (!bIsVisible)
	{
		SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	SetVisibility(ESlateVisibility::Visible);

	if (IsValid(DescriptionBlock))
	{
		DescriptionBlock->SetText(Description);
	}
	if (IsValid(ProgressBar))
	{
		TargetPercent = Percentage;
	}
}

void UAbilityProgressWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (ProgressBar)
	{
		// ProgressBar->SetPercent(TargetPercent);
		if (FMath::Abs(TargetPercent - DisplayedPercent) >= 0.05f)
		{
			ProgressBar->SetPercent(TargetPercent);
			DisplayedPercent = TargetPercent;
		}
		else
		{
			DisplayedPercent = FMath::FInterpTo(DisplayedPercent, TargetPercent, InDeltaTime, ProgressInterpSpeed);
			ProgressBar->SetPercent(DisplayedPercent);
		}
	}
}
