// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/UI/SelfCareWidget.h"

#include "Abilities/GameplayAbility.h"
#include "Components/ProgressBar.h"
#include "JMS/GAS/SurvivorAttributeSet.h"


void USelfCareWidget::OnAbilityActivated(UGameplayAbility* Ability)
{
	Super::OnAbilityActivated(Ability);
	if (Ability->GetClass() == GameplayAbilityClass)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	if (OwnerASC)
	{
		AttributeChangedDelegateHandle = OwnerASC->GetGameplayAttributeValueChangeDelegate(
			USurvivorAttributeSet::GetHealProgressAttribute()).AddUObject(
			this, &USelfCareWidget::AttributeChanged);
	}
}

void USelfCareWidget::OnAbilityDeactivated(UGameplayAbility* Ability)
{
	Super::OnAbilityDeactivated(Ability);
	if (Ability->GetClass() == GameplayAbilityClass)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	if (OwnerASC && AttributeChangedDelegateHandle.IsValid())
	{
		OwnerASC->GetGameplayAttributeValueChangeDelegate(USurvivorAttributeSet::GetHealProgressAttribute()).Remove(
			AttributeChangedDelegateHandle);
		AttributeChangedDelegateHandle.Reset();
	}
}

void USelfCareWidget::SetPercent(float Percent)
{
	ProgressBar->SetPercent(Percent);
}

void USelfCareWidget::AttributeChanged(const FOnAttributeChangeData& Data)
{
	SetPercent(Data.NewValue / CachedMaxValue);
}

void USelfCareWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (OwnerASC)
	{
		bool bFound;
		float CurValue = OwnerASC->GetGameplayAttributeValue(USurvivorAttributeSet::GetHealProgressAttribute(), bFound);
		CachedMaxValue = OwnerASC->GetGameplayAttributeValue(USurvivorAttributeSet::GetMaxHealProgressAttribute(),
		                                                     bFound);
		if (CachedMaxValue > 0.0f)
		{
			SetPercent(CurValue / CachedMaxValue);
		}
	}
	AttributeChangedDelegateHandle.Reset();
}
