// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GE/GE_HealSkillCheckBad.h"

#include "JMS/GAS/SurvivorAttributeSet.h"


UGE_HealSkillCheckBad::UGE_HealSkillCheckBad()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
	FGameplayModifierInfo ModifierInfo;
	
	FAttributeBasedFloat AttributeBasedFloat;
	AttributeBasedFloat.Coefficient = -0.15f;
	AttributeBasedFloat.BackingAttribute = FGameplayEffectAttributeCaptureDefinition(
		FGameplayEffectAttributeCaptureDefinition(USurvivorAttributeSet::GetMaxHealProgressAttribute(),
		                                          EGameplayEffectAttributeCaptureSource::Target, false));

	ModifierInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(AttributeBasedFloat);

	ModifierInfo.ModifierOp = EGameplayModOp::Additive;
	ModifierInfo.Attribute = USurvivorAttributeSet::GetHealProgressAttribute();
	Modifiers.Add(ModifierInfo);
}
