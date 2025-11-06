// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/UI/ProgressBarActivatedByTag.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/ProgressBar.h"
#include "Shared/DBDGameplayTags.h"



void UProgressBarActivatedByTag::TagChanged(const FGameplayTag Tag, int32 NewCount)
{
	if (NewCount>0)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UProgressBarActivatedByTag::SetPercent(float Percent)
{
	ProgressBar->SetPercent(Percent);
}

void UProgressBarActivatedByTag::AttributeChanged(const FOnAttributeChangeData& Data)
{
	SetPercent(Data.NewValue / CachedMaxValue);
}

void UProgressBarActivatedByTag::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UProgressBarActivatedByTag::NativeConstruct()
{
	Super::NativeConstruct();
	APawn* OwningPlayerPawn = GetOwningPlayerPawn();
	SetVisibility(ESlateVisibility::Hidden);
	if (!OwningPlayerPawn)
	{
		return;
	}
	UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwningPlayerPawn);
	if (OwnerASC)
	{
		bool bFound;
		float CurValue = OwnerASC->GetGameplayAttributeValue(CurrentValueAttribute, bFound);
		CachedMaxValue = OwnerASC->GetGameplayAttributeValue(MaxValueAttribute, bFound);
		if (CachedMaxValue > 0.0f)
		{
			SetPercent(CurValue / CachedMaxValue);
		}
		OwnerASC->GetGameplayAttributeValueChangeDelegate(CurrentValueAttribute).AddUObject(
			this, &UProgressBarActivatedByTag::AttributeChanged);
		OwnerASC->RegisterGameplayTagEvent(TargetTag).AddUObject(this, &UProgressBarActivatedByTag::TagChanged);
	}
}
