// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/ObjFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"

bool UObjFunctionLibrary::ActorHasGameplayTag(AActor* Actor, FGameplayTag Tag)
{
	UAbilitySystemComponent* ASC = NativeGetAbilitySystemComponent(Actor);
	if (ASC)
	{
		return ASC->HasMatchingGameplayTag(Tag);
	}
	return false;
}

UAbilitySystemComponent* UObjFunctionLibrary::NativeGetAbilitySystemComponent(AActor* Actor)
{
	check(Actor);

	return UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);
}

float UObjFunctionLibrary::GetStaticCooldownDurationForAbility(const UGameplayAbility* Ability)
{
	if (!Ability) return 0.f;

	const UGameplayEffect* CooldownEffect = Ability->GetCooldownGameplayEffect();
	if (!CooldownEffect) return 0.f;

	float CooldownDuration = 0.f;
	CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1, CooldownDuration);
	return CooldownDuration;
}

float UObjFunctionLibrary::GetStaticCostForAbility(const class UGameplayAbility* Ability)
{
	if (!Ability) return 0.f;

	const UGameplayEffect* CostEffect = Ability->GetCostGameplayEffect();
	if (!CostEffect) return 0.f;

	float Cost = 0.f;
	CostEffect->Modifiers[0].ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Cost);
	return FMath::Abs(Cost);
}