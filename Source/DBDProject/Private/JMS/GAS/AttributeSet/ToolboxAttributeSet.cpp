// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/AttributeSet/ToolboxAttributeSet.h"

#include "Net/UnrealNetwork.h"


void UToolboxAttributeSet::OnRep_ToolboxRepairSpeedMultiplier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UToolboxAttributeSet, ToolboxRepairSpeedMultiplier, OldValue);
}

void UToolboxAttributeSet::OnRep_ToolboxSabotageSpeedMultiplier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UToolboxAttributeSet, ToolboxSabotageSpeedMultiplier, OldValue);
}

void UToolboxAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UToolboxAttributeSet, ToolboxRepairSpeedMultiplier, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UToolboxAttributeSet, ToolboxSabotageSpeedMultiplier, COND_None, REPNOTIFY_Always);
}

void UToolboxAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}
