// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/AbilitySystem/KillerAttributeSet.h"

#include "Net/UnrealNetwork.h"


UKillerAttributeSet::UKillerAttributeSet()
{
	InitWalkingSpeed(1.f);
	InitStunRate(1.f);
	InitPickUpSpeedRate(1.f);
	InitTerrorRadiusRange(1.f);
	InitDestroyPalletRate(1.f);
	InitDamageGeneratorRate(1.f);
	InitAfterAttackRate(1.f);
}

void UKillerAttributeSet::OnRep_WalkingSpeed(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKillerAttributeSet, WalkingSpeed, OldValue);
	OnWalkingSpeedChanged.Broadcast(WalkingSpeed.GetCurrentValue());
}

float UKillerAttributeSet::SetCurrentWalkingSpeed(float NewValue)
{
	WalkingSpeed.SetCurrentValue(NewValue);
	OnWalkingSpeedChanged.Broadcast(NewValue);
	return NewValue;
}

void UKillerAttributeSet::OnRep_StunRate(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKillerAttributeSet, StunRate, OldValue);
}

void UKillerAttributeSet::OnRep_PickUpSpeedRate(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKillerAttributeSet, PickUpSpeedRate, OldValue);
}

void UKillerAttributeSet::OnRep_TerrorRadiusRange(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKillerAttributeSet, TerrorRadiusRange, OldValue);
}

void UKillerAttributeSet::OnRep_DestroyPalletRate(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKillerAttributeSet, DestroyPalletRate, OldValue);
}

void UKillerAttributeSet::OnRep_DamageGeneratorRate(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKillerAttributeSet, DamageGeneratorRate, OldValue);
}

void UKillerAttributeSet::OnRep_AfterAttackRate(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKillerAttributeSet, AfterAttackRate, OldValue);
}

void UKillerAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UKillerAttributeSet, WalkingSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UKillerAttributeSet, StunRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UKillerAttributeSet, PickUpSpeedRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UKillerAttributeSet, TerrorRadiusRange, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UKillerAttributeSet, DestroyPalletRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UKillerAttributeSet, DamageGeneratorRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UKillerAttributeSet, AfterAttackRate, COND_None, REPNOTIFY_Always);
	//DOREPLIFETIME_CONDITION_NOTIFY(UKillerAttributeSet, WalkingSpeed.GetCurrentValue(), COND_None, REPNOTIFY_Always);
	
}

