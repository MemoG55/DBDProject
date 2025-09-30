// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/GE/ObjGE_HookHp.h"

#include "JMS/GAS/SurvivorAttributeSet.h"
#include "Shared/DBDGameplayTags.h"

UObjGE_HookHp::UObjGE_HookHp()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	// Set MaxTask
	{
		FSetByCallerFloat HookHpSBC;
		HookHpSBC.DataTag = DBDGameplayTags::Object_Progress_OnProgress;
		FGameplayEffectModifierMagnitude HookHPMagnitude;
		
		FGameplayModifierInfo HookHpMod;
		HookHpMod.Attribute = USurvivorAttributeSet::GetHookHPAttribute();
		HookHpMod.ModifierOp = EGameplayModOp::Override;
		HookHpMod.ModifierMagnitude = FGameplayEffectModifierMagnitude(HookHpSBC);
			
		Modifiers.Add(HookHpMod);
	}
}
