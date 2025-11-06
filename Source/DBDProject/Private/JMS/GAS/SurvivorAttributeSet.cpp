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

void USurvivorAttributeSet::OnRep_SprintSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, SprintSpeed, OldValue);
}

void USurvivorAttributeSet::OnRep_CrouchSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, CrouchSpeed, OldValue);
}

void USurvivorAttributeSet::OnRep_CrawlSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, CrawlSpeed, OldValue);
}

void USurvivorAttributeSet::OnRep_InteractSpeed_Generator(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, InteractSpeed_Generator, OldValue);
}

void USurvivorAttributeSet::OnRep_InteractSpeed_ExitDoor(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, InteractSpeed_ExitDoor, OldValue);
}

void USurvivorAttributeSet::OnRep_InteractSpeed_Chest(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, InteractSpeed_Chest, OldValue);
}

void USurvivorAttributeSet::OnRep_InteractSpeed_TotemCleansing(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, InteractSpeed_TotemCleansing, OldValue);
}

void USurvivorAttributeSet::OnRep_HealSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, HealSpeed, OldValue);
}

void USurvivorAttributeSet::OnRep_HookSabotageSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, HookSabotageSpeed, OldValue);
}

void USurvivorAttributeSet::OnRep_RescueSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, RescueSpeed, OldValue);
}

void USurvivorAttributeSet::OnRep_SkillCheckFrequency(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, SkillCheckFrequency, OldValue);
}

void USurvivorAttributeSet::OnRep_QuickActionSoundVolume(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, QuickActionSoundVolume, OldValue);
}

void USurvivorAttributeSet::OnRep_CurrentItemCharge(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, CurrentItemCharge, OldValue);
	// OnCurrentItemChargeChanged.ExecuteIfBound(GetCurrentItemCharge() / GetMaxItemCharge());
}

void USurvivorAttributeSet::OnRep_MaxItemCharge(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USurvivorAttributeSet, MaxItemCharge, OldValue);
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
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, SprintSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, CrouchSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, CrawlSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, InteractSpeed_Generator, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, InteractSpeed_ExitDoor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, InteractSpeed_Chest, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, InteractSpeed_TotemCleansing, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, HealSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, HookSabotageSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, RescueSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, SkillCheckFrequency, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, QuickActionSoundVolume, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, CurrentItemCharge, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USurvivorAttributeSet, MaxItemCharge, COND_None, REPNOTIFY_Always);
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
		else if (NewValue > 0.f && NewValue <= 50.f)
		{
			if (!GetOwningAbilitySystemComponent()->HasMatchingGameplayTag(
				DBDGameplayTags::Survivor_Status_HookedPhase2))
			{
				GetOwningAbilitySystemComponent()->AddLooseGameplayTag(DBDGameplayTags::Survivor_Status_HookedPhase2);
				GetOwningAbilitySystemComponent()->AddReplicatedLooseGameplayTag(
					DBDGameplayTags::Survivor_Status_HookedPhase2);
			}
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
	if (Attribute == GetCurrentItemChargeAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxItemCharge());
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

	if (Data.EvaluatedData.Attribute == GetCurrentItemChargeAttribute())
	{
		SetCurrentItemCharge(FMath::Clamp(GetCurrentItemCharge(), 0.f, GetMaxItemCharge()));
	}
}
