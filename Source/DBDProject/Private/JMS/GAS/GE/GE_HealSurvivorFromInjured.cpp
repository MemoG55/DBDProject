// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GE/GE_HealSurvivorFromInjured.h"

#include "JMS/GAS/SurvivorAttributeSet.h"
#include "Shared/DBDGameplayTags.h"


UGE_HealSurvivorFromInjured::UGE_HealSurvivorFromInjured()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
	FGameplayModifierInfo SetbyCallerMod;
	FSetByCallerFloat SetbyCallerFloat;
	SetbyCallerFloat.DataName = NAME_None;
	SetbyCallerFloat.DataTag = DBDGameplayTags::Survivor_SetbyCaller_HealAmount;
	SetbyCallerMod.ModifierMagnitude = FGameplayEffectModifierMagnitude(SetbyCallerFloat);
	SetbyCallerMod.ModifierOp = EGameplayModOp::Additive;
	SetbyCallerMod.Attribute = USurvivorAttributeSet::GetHealProgressAttribute();
	Modifiers.Add(SetbyCallerMod);
}
