// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/UI/SurvivorItemPickupWidget.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Shared/DBDGameplayTags.h"


void USurvivorItemPickupWidget::NativeConstruct()
{
	Super::NativeConstruct();
	APawn* OwningPlayerPawn = GetOwningPlayerPawn();
	if (!OwningPlayerPawn)
	{
		return;
	}
	if (UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwningPlayerPawn))
	{
		OwnerASC->RegisterGameplayTagEvent(DBDGameplayTags::Interactable_Object_SurvivorItem).AddUObject(
			this, &USurvivorItemPickupWidget::OnItemInteractableTagChanged);
	}
}

void USurvivorItemPickupWidget::OnItemInteractableTagChanged(const FGameplayTag Tag, int32 NewCount)
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
