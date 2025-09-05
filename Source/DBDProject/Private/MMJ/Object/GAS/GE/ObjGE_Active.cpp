// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/GE/ObjGE_Active.h"

#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "Shared/DBDGameplayTags.h"

UObjGE_Active::UObjGE_Active()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;

	UTargetTagsGameplayEffectComponent* Component = CreateDefaultSubobject<UTargetTagsGameplayEffectComponent>("Grant Tag To Target");
	if (Component)
	{
		FInheritedTagContainer Tags;
		Tags.AddTag(DBDGameplayTags::Object_Status_IsActive);
		
		Component->SetAndApplyTargetTagChanges(Tags);
		GEComponents.Add(Component);
	}
}
