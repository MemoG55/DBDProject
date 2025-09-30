// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/ObjAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

bool UObjAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UObjAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetCurrentTaskAttribute())
	{
		SetCurrentTask(FMath::Clamp(GetCurrentTask(), 0.f, GetMaxTask()));
	}

	if (Data.EvaluatedData.Attribute == GetCurrentDamageAttribute())
	{
		SetCurrentDamage(FMath::Clamp(GetCurrentDamage(), 0.f, GetMaxDamage()));
	}
}

void UObjAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetCurrentTaskAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxTask());
	}

	if (Attribute == GetCurrentDamageAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxDamage());
	}
}

void UObjAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void UObjAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
}

void UObjAttributeSet::PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue,
	float NewValue) const
{
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);
}

void UObjAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate
	DOREPLIFETIME_CONDITION_NOTIFY(UObjAttributeSet, MaxTask, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UObjAttributeSet, CurrentTask, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UObjAttributeSet, MaxDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UObjAttributeSet, CurrentDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UObjAttributeSet, RecoverTask, COND_None, REPNOTIFY_Always);
}

void UObjAttributeSet::OnRep_MaxTask(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UObjAttributeSet, MaxTask, OldValue);
}

void UObjAttributeSet::OnRep_CurrentTask(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UObjAttributeSet, CurrentTask, OldValue);
}

void UObjAttributeSet::OnRep_MaxDamage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UObjAttributeSet, MaxDamage, OldValue);
}

void UObjAttributeSet::OnRep_CurrentDamage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UObjAttributeSet, CurrentDamage, OldValue);
}

void UObjAttributeSet::OnRep_RecoverTask(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UObjAttributeSet, RecoverTask, OldValue);
}
