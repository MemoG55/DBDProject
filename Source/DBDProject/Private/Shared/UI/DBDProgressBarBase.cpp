// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/DBDProgressBarBase.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Shared/GAS/DBDAbilitySystemComponent.h"


void UDBDProgressBarBase::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDBDProgressBarBase::Display()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UDBDProgressBarBase::SetObjectASC(UDBDAbilitySystemComponent* ASC, const FGameplayAttribute& CurrentAttribute,
                                       const FGameplayAttribute& MaxAttribute)
{
	// TODO :: InteractTitle, InteractImage, InteractKeyGuide

	if (OwnerASC)
	{
		bool bFound = false;
		float MaxValue = OwnerASC->GetGameplayAttributeValue(MaxAttribute, bFound);
		float CurrentValue = OwnerASC->GetGameplayAttributeValue(CurrentAttribute, bFound);

		if (bFound)
		{
			UpdateMaxValue(MaxValue);
			UpdateCurrentValue(CurrentValue);
		}
		
		OwnerASC->GetGameplayAttributeValueChangeDelegate(CurrentAttribute).RemoveAll(this);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(MaxAttribute).RemoveAll(this);
		
		OwnerASC = nullptr;
	}
	if (IsValid(ASC))
	{
		OwnerASC = ASC;
		bool bFound = false;
		float MaxValue = ASC->GetGameplayAttributeValue(MaxAttribute, bFound);
		float CurrentValue = ASC->GetGameplayAttributeValue(CurrentAttribute, bFound);

		if (bFound)
		{
			UpdateMaxValue(MaxValue);
			UpdateCurrentValue(CurrentValue);
		}
		
		ASC->GetGameplayAttributeValueChangeDelegate(CurrentAttribute).AddUObject(this, &ThisClass::UpdateCurrentValueByAttribute);
		ASC->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this, &ThisClass::UpdateMaxValueByAttribute);
	}
}

void UDBDProgressBarBase::UpdateCurrentValueByAttribute(const FOnAttributeChangeData& ChangeData)
{
	UpdateCurrentValue(ChangeData.NewValue);
}

void UDBDProgressBarBase::UpdateMaxValueByAttribute(const FOnAttributeChangeData& ChangeData)
{
	UpdateMaxValue(ChangeData.NewValue);
}

void UDBDProgressBarBase::UpdateCurrentValue(float NewValue)
{
	CachedCurrentValue = NewValue;
	Update();
}

void UDBDProgressBarBase::UpdateMaxValue(float NewValue)
{
	CachedMaxValue = NewValue;
	Update();
}

void UDBDProgressBarBase::Update()
{
	if (CachedMaxValue <= 0) return;
	float NewPercent = CachedCurrentValue / CachedMaxValue;
	if (IsValid(ProgressBar))
	{
		ProgressBar->SetPercent(NewPercent);
		CachedPercent = NewPercent;

		if (IsValid(CurrentProgressMarking))
		{
			if (UCanvasPanelSlot* MarkerSlot = Cast<UCanvasPanelSlot>(CurrentProgressMarking->Slot))
			{
				FGeometry BarGeometry = ProgressBar->GetCachedGeometry();
				float BarLength = BarGeometry.GetLocalSize().X;

				float MarkerWidth = MarkerSlot->GetSize().X;

				float NewXPosition = (BarLength * CachedPercent) - (MarkerWidth / 2.f);

				FVector2D CurrentPosition = MarkerSlot->GetPosition();
				FVector2D NewPosition(NewXPosition, CurrentPosition.Y);

				MarkerSlot->SetPosition(NewPosition);
			}
		}
	}
}
