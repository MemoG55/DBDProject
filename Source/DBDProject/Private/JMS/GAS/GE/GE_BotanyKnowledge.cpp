// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GE/GE_BotanyKnowledge.h"

#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "JMS/GAS/SurvivorAttributeSet.h"
#include "Shared/DBDGameplayTags.h"


UGE_BotanyKnowledge::UGE_BotanyKnowledge()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	FGameplayModifierInfo HealSpeedMod;;
	HealSpeedMod.Attribute = USurvivorAttributeSet::GetHealSpeedAttribute();
	HealSpeedMod.ModifierOp = EGameplayModOp::Multiplicitive;
	HealSpeedMod.ModifierMagnitude = FScalableFloat(HealSpeedMultiplier);
	Modifiers.Add(HealSpeedMod);

	UTargetTagsGameplayEffectComponent* Component = CreateDefaultSubobject<UTargetTagsGameplayEffectComponent>("Grant Tag To Target");
	if (Component)
	{
		FInheritedTagContainer Tags;
		Tags.AddTag(DBDGameplayTags::Survivor_Status_BotanyKnowledge);
		
		Component->SetAndApplyTargetTagChanges(Tags);
		GEComponents.Add(Component);
	}
}
