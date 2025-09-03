// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/SurvivorAttributeSet.h"

#include "Net/UnrealNetwork.h"

void USurvivorAttributeSet::OnRep_HookHP(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, HookHP, OldValue);
}

void USurvivorAttributeSet::OnRep_DyingHP(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, DyingHP, OldValue);
}

void USurvivorAttributeSet::OnRep_HealProgress(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, HealProgress, OldValue);
}

void USurvivorAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, MovementSpeed, OldValue);
}

void USurvivorAttributeSet::OnRep_GeneratorRepairSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, GeneratorRepairSpeed, OldValue);
}


void USurvivorAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, HookHP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, DyingHP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, HealProgress, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, GeneratorRepairSpeed, COND_None, REPNOTIFY_Always);
}
