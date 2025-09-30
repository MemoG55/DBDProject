// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/GAS/GE/GE_GrantBlindTagForDuration.h"

#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "Shared/DBDGameplayTags.h"


UGE_GrantBlindTagForDuration::UGE_GrantBlindTagForDuration()
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(2.f));
	StackingType = EGameplayEffectStackingType::AggregateByTarget;
	StackLimitCount = 1;
	

	UTargetTagsGameplayEffectComponent* Component = CreateDefaultSubobject<UTargetTagsGameplayEffectComponent>(
		"Grant Tag To Target");
	if (Component)
	{
		FInheritedTagContainer Tags;
		Tags.AddTag(DBDGameplayTags::Shared_Status_Blind);

		Component->SetAndApplyTargetTagChanges(Tags);
		GEComponents.Add(Component);
	}
}
