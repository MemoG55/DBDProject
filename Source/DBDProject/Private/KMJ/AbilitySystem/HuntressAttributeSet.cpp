// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/AbilitySystem/HuntressAttributeSet.h"

#include "Net/UnrealNetwork.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDGameplayTags.h"

UHuntressAttributeSet::UHuntressAttributeSet()
{
}

void UHuntressAttributeSet::OnRep_LullabyRadiusRange(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHuntressAttributeSet, LullabyRadiusRange, OldValue);
}

void UHuntressAttributeSet::OnRep_AxeNumber(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHuntressAttributeSet, AxeNumber, OldValue);
	OnAxeNumberChanged.Broadcast(AxeNumber.GetCurrentValue());
}

void UHuntressAttributeSet::SetCurrentAxeNum(float NewAxeNum)
{
	AxeNumber.SetCurrentValue(NewAxeNum);
	OnAxeNumberChanged.Broadcast(NewAxeNum);
}

void UHuntressAttributeSet::OnRep_RefillAxeFromCabinetRate(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHuntressAttributeSet, RefillAxeFromCabinetRate, OldValue);
}

void UHuntressAttributeSet::OnRep_ChargingAxeMinRate(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHuntressAttributeSet, ChargingAxeMinRate, OldValue);
}

void UHuntressAttributeSet::OnRep_ChargingAxeMaxRate(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHuntressAttributeSet, ChargingAxeMaxRate, OldValue);
}

void UHuntressAttributeSet::OnRep_AxeMaxSpeed(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHuntressAttributeSet, AxeMaxSpeed, OldValue);
}

void UHuntressAttributeSet::OnRep_AxeMinSpeed(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHuntressAttributeSet, AxeMinSpeed, OldValue);
}

void UHuntressAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UHuntressAttributeSet, LullabyRadiusRange, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHuntressAttributeSet, AxeNumber, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHuntressAttributeSet, RefillAxeFromCabinetRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHuntressAttributeSet, ChargingAxeMinRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHuntressAttributeSet, ChargingAxeMaxRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHuntressAttributeSet, AxeMaxSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHuntressAttributeSet, AxeMinSpeed, COND_None, REPNOTIFY_Always);
}
