// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GE/GE_SurvivorResetHealProgress.h"

#include "JMS/GAS/SurvivorAttributeSet.h"


UGE_SurvivorResetHealProgress::UGE_SurvivorResetHealProgress()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
	FGameplayModifierInfo OverrideAttributeMod;
	OverrideAttributeMod.Attribute = USurvivorAttributeSet::GetHealProgressAttribute();
	OverrideAttributeMod.ModifierMagnitude = FScalableFloat(0.0f);
	OverrideAttributeMod.ModifierOp = EGameplayModOp::Override;
	Modifiers.Add(OverrideAttributeMod);
}
