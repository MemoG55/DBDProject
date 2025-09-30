// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/TempAttributeUI.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/TextBlock.h"
#include "KMJ/AbilitySystem/HuntressAttributeSet.h"
#include "Shared/DBDDebugHelper.h"


void UTempAttributeUI::SetValue(float NewValue)
{
	AttributeText->SetText(FText::Format(
		NSLOCTEXT("UI", "ShowAttribute", "{0}: {1}"),
		AttributeDescription, FText::AsNumber(NewValue, &NumberFormattingOptions)
	));
}

void UTempAttributeUI::AttributeChanged(const FOnAttributeChangeData& Data)
{
	SetValue(Data.NewValue);
}

void UTempAttributeUI::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UTempAttributeUI::NativeConstruct()
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
		bool bFound;
		float AttrValue = OwnerASC->GetGameplayAttributeValue(Attribute, bFound);
		SetValue(AttrValue);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(
			this, &UTempAttributeUI::AttributeChanged);
	}
}
