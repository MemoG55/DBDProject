// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GE/GE_BotanyKnowledge.h"

#include "JMS/GAS/SurvivorAttributeSet.h"


UGE_BotanyKnowledge::UGE_BotanyKnowledge()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	FGameplayModifierInfo HealSpeedMod;;
	HealSpeedMod.Attribute = USurvivorAttributeSet::GetHealSpeedAttribute();
	HealSpeedMod.ModifierOp = EGameplayModOp::Multiplicitive;
	HealSpeedMod.ModifierMagnitude = FScalableFloat(HealSpeedMultiplier);
	Modifiers.Add(HealSpeedMod);
}
