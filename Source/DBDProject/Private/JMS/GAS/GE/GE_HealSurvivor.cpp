// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GE/GE_HealSurvivor.h"

#include "JMS/GAS/SurvivorAttributeSet.h"
#include "Shared/DBDGameplayTags.h"


UGE_HealSurvivor::UGE_HealSurvivor()
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
