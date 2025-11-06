// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/AttributeSet/MedkitAttributeSet.h"

#include "Net/UnrealNetwork.h"


void UMedkitAttributeSet::OnRep_MedKitHealSpeedMultiplier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedkitAttributeSet, MedKitHealSpeedMultiplier, OldValue);

}

void UMedkitAttributeSet::OnRep_MedKitSelfHealSpeedMultiplier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMedkitAttributeSet, MedKitSelfHealSpeedMultiplier, OldValue);
}

void UMedkitAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedkitAttributeSet, MedKitHealSpeedMultiplier, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMedkitAttributeSet, MedKitSelfHealSpeedMultiplier, COND_None, REPNOTIFY_Always);
}

void UMedkitAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}
