// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/SurvivorAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "Shared/DBDGameplayTags.h"

void USurvivorAttributeSet::OnRep_MaxHookHP(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, MaxHookHP, OldValue);
}

void USurvivorAttributeSet::OnRep_HookHP(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, HookHP, OldValue);
}

void USurvivorAttributeSet::OnRep_MaxDyingHP(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, MaxDyingHP, OldValue);
}

void USurvivorAttributeSet::OnRep_DyingHP(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, DyingHP, OldValue);
}

void USurvivorAttributeSet::OnRep_MaxHealProgress(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, MaxHealProgress, OldValue);
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

void USurvivorAttributeSet::OnRep_HealSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, HealSpeed, OldValue);
}

void USurvivorAttributeSet::OnRep_SkillCheckFrequency(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, SkillCheckFrequency, OldValue);
}


void USurvivorAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, MaxHookHP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, HookHP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, MaxDyingHP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, DyingHP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, MaxHealProgress, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, HealProgress, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, GeneratorRepairSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, HealSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, SkillCheckFrequency, COND_None, REPNOTIFY_Always);
}

void USurvivorAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHookHPAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHookHP());
		if (NewValue <= 0.f)
		{
			GetOwningAbilitySystemComponent()->AddLooseGameplayTag(DBDGameplayTags::Survivor_Status_Dead);
			GetOwningAbilitySystemComponent()->AddReplicatedLooseGameplayTag(DBDGameplayTags::Survivor_Status_Dead);
		}
	}
	if (Attribute == GetDyingHPAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxDyingHP());		
	}
	if (Attribute == GetHealProgressAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealProgress());
	}
}

void USurvivorAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

}

void USurvivorAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetHealProgressAttribute())
	{
		SetHealProgress(FMath::Clamp(GetHealProgress(), 0.f, GetMaxHealProgress()));
	}

	if (Data.EvaluatedData.Attribute == GetDyingHPAttribute())
	{
		SetDyingHP(FMath::Clamp(GetDyingHP(), 0.f, GetMaxDyingHP()));
	}

	if (Data.EvaluatedData.Attribute == GetHookHPAttribute())
	{
		SetHookHP(FMath::Clamp(GetHookHP(), 0.f, GetMaxHookHP()));
	}
}
