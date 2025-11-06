// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/ActivatableActionIndicator.h"

#include "Shared/Character/DBDCharacter.h"
#include "Shared/GAS/DBDAbilitySystemComponent.h"


void UActivatableActionIndicator::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Collapsed);
	if (ADBDCharacter* OwnerDBDCharacter = Cast<ADBDCharacter>(GetOwningPlayerPawn()))
	{
		OwnerDBDCharacterASC = Cast<UDBDAbilitySystemComponent>(OwnerDBDCharacter->GetAbilitySystemComponent());
	}
	OwnerDBDCharacterASC->RegisterGameplayTagEvent(VisibleTag).
	                      AddUObject(this, &UActivatableActionIndicator::OnVisibleTagChanged);
	for (FGameplayTag HideTag : HideTags)
	{
		OwnerDBDCharacterASC->RegisterGameplayTagEvent(HideTag).
		                      AddUObject(this, &UActivatableActionIndicator::OnHideTagChanged);
	}
}

void UActivatableActionIndicator::OnVisibleTagChanged(const FGameplayTag Tag, int32 NewCount)
{
	if (NewCount > 0 && !OwnerDBDCharacterASC->HasAnyMatchingGameplayTags(HideTags))
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UActivatableActionIndicator::OnHideTagChanged(const FGameplayTag Tag, int32 NewCount)
{
	if (NewCount > 0)
	{
		SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		if (OwnerDBDCharacterASC->HasMatchingGameplayTag(VisibleTag)&& !OwnerDBDCharacterASC->HasAnyMatchingGameplayTags(HideTags))
		{
			SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}
