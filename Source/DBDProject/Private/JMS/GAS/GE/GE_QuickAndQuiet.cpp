// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GE/GE_QuickAndQuiet.h"

#include "GameplayEffectComponents/AssetTagsGameplayEffectComponent.h"
#include "JMS/GAS/SurvivorAttributeSet.h"


UGE_QuickAndQuiet::UGE_QuickAndQuiet()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	FGameplayModifierInfo OverrideAttributeMod;
	OverrideAttributeMod.Attribute = USurvivorAttributeSet::GetQuickActionSoundVolumeAttribute();
	OverrideAttributeMod.ModifierMagnitude = FScalableFloat(0.1f);
	OverrideAttributeMod.ModifierOp = EGameplayModOp::Multiplicitive;
	Modifiers.Add(OverrideAttributeMod);
}
