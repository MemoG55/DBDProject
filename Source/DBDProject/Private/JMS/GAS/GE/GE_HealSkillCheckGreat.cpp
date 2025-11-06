// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GE/GE_HealSkillCheckGreat.h"

#include "JMS/GAS/SurvivorAttributeSet.h"


UGE_HealSkillCheckGreat::UGE_HealSkillCheckGreat()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
	FGameplayModifierInfo ModifierInfo;
	
	FAttributeBasedFloat AttributeBasedFloat;
	AttributeBasedFloat.Coefficient = 0.3f;
	AttributeBasedFloat.BackingAttribute = FGameplayEffectAttributeCaptureDefinition(
		FGameplayEffectAttributeCaptureDefinition(USurvivorAttributeSet::GetMaxHealProgressAttribute(),
												  EGameplayEffectAttributeCaptureSource::Target, false));

	ModifierInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(AttributeBasedFloat);

	ModifierInfo.ModifierOp = EGameplayModOp::Additive;
	ModifierInfo.Attribute = USurvivorAttributeSet::GetHealProgressAttribute();
	Modifiers.Add(ModifierInfo);
}
