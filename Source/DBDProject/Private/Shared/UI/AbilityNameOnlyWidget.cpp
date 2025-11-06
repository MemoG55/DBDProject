// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/AbilityNameOnlyWidget.h"

#include "Components/TextBlock.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/UI/DBDWidgetComponent.h"


void UAbilityNameOnlyWidget::OnSetVisibilityAndText(bool bIsVisible, FText Description)
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
}

void UAbilityNameOnlyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ADBDCharacter* OwningPlayerPawn = Cast<ADBDCharacter>(GetOwningPlayerPawn());
	if (OwningPlayerPawn)
	{
		OwningPlayerPawn->GetWidgetComponent()->OnUpdateAbilityNameOnlyWidget.AddDynamic(this, &UAbilityNameOnlyWidget::OnSetVisibilityAndText);
	}
}
