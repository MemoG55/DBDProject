// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/GAS/DBDAbilitySystemComponent.h"
#include "KillerAbilitySystemComponent.generated.h"
class AKillerHuntress;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UKillerAbilitySystemComponent : public UDBDAbilitySystemComponent
{
	GENERATED_BODY()
public:
	UKillerAbilitySystemComponent();
private:
	UPROPERTY(EditDefaultsOnly, Category="GameplayEffects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;

	UPROPERTY(EditDefaultsOnly, Category="DataControl")
	class UDA_KillerGameplayAbilities* GAData;
public:
	void ApplyInitializeEffects();
	void OperatingInitializedAbilities();
	void ApplyFullStatEffect();

private:
	void AuthApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect, int Level);
};
