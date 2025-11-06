// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/UI/AbilityWidgetBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


void UAbilityWidgetBase::OnAbilityActivated(UGameplayAbility* Ability)
{
	// 자식에서 구현
}

void UAbilityWidgetBase::OnAbilityDeactivated(UGameplayAbility* Ability)
{
	// 자식에서 구현
}

void UAbilityWidgetBase::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UAbilityWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	OwningPlayerPawn = GetOwningPlayerPawn();
	SetVisibility(ESlateVisibility::Collapsed);
	if (!OwningPlayerPawn)
	{
		return;
	}
	OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwningPlayerPawn);
	if (OwnerASC)
	{
		OwnerASC->AbilityActivatedCallbacks.AddUObject(this, &UAbilityWidgetBase::OnAbilityActivated);
		OwnerASC->AbilityEndedCallbacks.AddUObject(this,&UAbilityWidgetBase::OnAbilityDeactivated);
	}
}
