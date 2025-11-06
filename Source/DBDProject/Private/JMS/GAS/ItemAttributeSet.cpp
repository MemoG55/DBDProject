// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/ItemAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"


void UItemAttributeSet::OnRep_CurrentCharge(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UItemAttributeSet, CurrentCharge, OldValue);
}

void UItemAttributeSet::OnRep_MaxCharge(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UItemAttributeSet, MaxCharge, OldValue);
}

void UItemAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UItemAttributeSet, CurrentCharge, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UItemAttributeSet, MaxCharge, COND_None, REPNOTIFY_Always);
}

void UItemAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetCurrentChargeAttribute())
	{
 		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxCharge());
	}
	Super::PreAttributeChange(Attribute, NewValue);
}

void UItemAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
}


