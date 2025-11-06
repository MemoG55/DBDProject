// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared//UI/EffectWidgetBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/TextBlock.h"


void UEffectWidgetBase::TagChanged(const FGameplayTag Tag, int32 NewCount)
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

void UEffectWidgetBase::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UEffectWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	APawn* OwningPlayerPawn = GetOwningPlayerPawn();
	if (!OwningPlayerPawn)
	{
		return;
	}
	UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwningPlayerPawn);
	if (OwnerASC)
	{
		OwnerASC->RegisterGameplayTagEvent(TargetTag).AddUObject(this, &UEffectWidgetBase::TagChanged);
	}
	
}
