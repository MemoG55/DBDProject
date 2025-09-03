// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/GE/ObjGE_Init.h"

#include "MMJ/Object/GAS/ObjAttributeSet.h"

UObjGE_Init::UObjGE_Init()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	// Set MaxTask
	{
		FGameplayModifierInfo MaxTaskMod;
		MaxTaskMod.Attribute = UObjAttributeSet::GetMaxTaskAttribute();
		MaxTaskMod.ModifierOp = EGameplayModOp::Override;
		MaxTaskMod.ModifierMagnitude = FScalableFloat(MaxTask);
		Modifiers.Add(MaxTaskMod);
	}
}
