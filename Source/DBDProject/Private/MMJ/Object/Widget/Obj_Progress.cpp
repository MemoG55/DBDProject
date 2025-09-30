// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Widget/Obj_Progress.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/ProgressBar.h"

void UObj_Progress::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Visible);
}

void UObj_Progress::UpdateCurrentValue(const FOnAttributeChangeData& ChangeData)
{
	UpdateValue(ChangeData.NewValue, CachedMaxValue);
}

void UObj_Progress::UpdateMaxValue(const FOnAttributeChangeData& ChangeData)
{
	UpdateValue(CachedCurrentValue, ChangeData.NewValue);
}

void UObj_Progress::SetDisplay(bool IsDisplay)
{
	SetVisibility(IsDisplay ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UObj_Progress::SetObjectASC(UObjAbilitySystemComponent* ASC, const FGameplayAttribute& CurrentAttribute,
                                 const FGameplayAttribute& MaxAttribute)
{
	if (ASC)
	{
		bool bFound = false;
		float CurrentValue = ASC->GetGameplayAttributeValue(CurrentAttribute, bFound);
		float MaxValue = ASC->GetGameplayAttributeValue(MaxAttribute, bFound);

		if (bFound)
		{
			SetDisplay(true);
			UpdateValue(CurrentValue, MaxValue);
		}
		
		ASC->GetGameplayAttributeValueChangeDelegate(CurrentAttribute).AddUObject(this, &ThisClass::UpdateCurrentValue);
		ASC->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this, &ThisClass::UpdateMaxValue);
	}
	else
	{
		SetDisplay(false);
	}
}

void UObj_Progress::UpdateValue(float CurrentValue, float MaxValue)
{
	if (MaxValue <= 0) return;
	CachedCurrentValue = CurrentValue;
	CachedMaxValue = MaxValue;

	float NewPercent = CurrentValue / MaxValue;
	if (ProgressBar)
	{
		ProgressBar->SetPercent(NewPercent);
	}
}
