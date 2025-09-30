// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KMJ/DataAsset/DA_KillerGameplayAbilities.h"
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
	
	virtual void InitializeBaseAttributes() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="GameplayEffects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;
	
	/*UPROPERTY(EditDefaultsOnly, Category="DataControl")
	class UDA_KillerGameplayAbilities* GAData;*/
public:
	virtual void ApplyInitializeEffects() override;
	virtual void OperatingInitializedAbilities() override;
	//void ApplyFullStatEffect();

	FORCEINLINE UDA_KillerGameplayAbilities* GetKillerGAData() const
	{
		return Cast<UDA_KillerGameplayAbilities>(DBDASCData);
	}

private:
	virtual void AuthApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect, int Level) override;
};
