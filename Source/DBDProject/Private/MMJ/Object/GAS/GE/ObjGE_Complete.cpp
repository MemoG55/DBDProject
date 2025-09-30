// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/GE/ObjGE_Complete.h"

#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "Shared/DBDGameplayTags.h"

UObjGE_Complete::UObjGE_Complete()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;

	UTargetTagsGameplayEffectComponent* Component = CreateDefaultSubobject<UTargetTagsGameplayEffectComponent>("Grant Tag To Target");
	if (Component)
	{
		FInheritedTagContainer Tags;
		Tags.AddTag(DBDGameplayTags::Object_Status_IsComplete);
		
		Component->SetAndApplyTargetTagChanges(Tags);
		GEComponents.Add(Component);
	}
}
