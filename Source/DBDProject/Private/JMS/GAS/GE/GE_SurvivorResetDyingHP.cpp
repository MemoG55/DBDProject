// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GE/GE_SurvivorResetDyingHP.h"

#include "JMS/GAS/SurvivorAttributeSet.h"


UGE_SurvivorResetDyingHP::UGE_SurvivorResetDyingHP()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
	FGameplayModifierInfo OverrideAttributeMod;
	OverrideAttributeMod.Attribute = USurvivorAttributeSet::GetDyingHPAttribute();
	OverrideAttributeMod.ModifierMagnitude = FScalableFloat(0.0f);
	OverrideAttributeMod.ModifierOp = EGameplayModOp::Override;
	Modifiers.Add(OverrideAttributeMod);
}
