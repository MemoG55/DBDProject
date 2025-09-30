// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared//UI/TempUIReactToTag.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/TextBlock.h"


void UTempUIReactToTag::TagChanged(const FGameplayTag Tag, int32 NewCount)
{
	if (NewCount > 0)
	{
		DescriptionText->SetColorAndOpacity(FSlateColor(FLinearColor(0.f, 1.f, 0.f)));
	}
	else
	{
		DescriptionText->SetColorAndOpacity(FSlateColor(FLinearColor(.5f, .5f, .5f)));
	}
}

void UTempUIReactToTag::NativePreConstruct()
{
	Super::NativePreConstruct();
	DescriptionText->SetText(Description);
	DescriptionText->SetColorAndOpacity(FSlateColor(FLinearColor(.5f, .5f, .5f)));
}

void UTempUIReactToTag::NativeConstruct()
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
		OwnerASC->RegisterGameplayTagEvent(TargetTag).AddUObject(this, &UTempUIReactToTag::TagChanged);
	}
	
}
