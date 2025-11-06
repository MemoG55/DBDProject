// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/UI/EffectIconWidget.h"

#include "AbilitySystemComponent.h"
#include "JMS/Character/SurvivorCharacter.h"


void UEffectIconWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Collapsed);
	ASurvivorCharacter* OwningPlayerPawn = Cast<ASurvivorCharacter>(GetOwningPlayerPawn());
	if (OwningPlayerPawn)
	{
		CachedOwnerASC = OwningPlayerPawn->GetAbilitySystemComponent();
		if (CachedOwnerASC)
		{
			CachedOwnerASC->RegisterGameplayTagEvent(EffectTag).
			                AddUObject(this, &UEffectIconWidget::OnEffectTagChanged);
			for (FGameplayTag AnyTag : AdditionalAnyRequiredTags)
			{
				CachedOwnerASC->RegisterGameplayTagEvent(AnyTag).
				                AddUObject(this, &UEffectIconWidget::OnAdditionalAnyRequiredTagsChanged);
			}
		}
	}
}

void UEffectIconWidget::OnEffectTagChanged(const FGameplayTag Tag, int32 NewCount)
{
	if (NewCount > 0)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UEffectIconWidget::OnAdditionalAnyRequiredTagsChanged(const FGameplayTag Tag, int32 NewCount)
{
	if (!CachedOwnerASC->HasAllMatchingGameplayTags(FGameplayTagContainer(EffectTag)))
	{
		SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	if (CachedOwnerASC->HasAnyMatchingGameplayTags(AdditionalAnyRequiredTags))
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Collapsed);
	}
}
