// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "MedkitAttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
UCLASS()
class DBDPROJECT_API UMedkitAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
private:
	UPROPERTY(ReplicatedUsing=OnRep_MedKitHealSpeedMultiplier)
	FGameplayAttributeData MedKitHealSpeedMultiplier;
	UFUNCTION()
	void OnRep_MedKitHealSpeedMultiplier(const FGameplayAttributeData& OldValue);

	UPROPERTY(ReplicatedUsing=OnRep_MedKitSelfHealSpeedMultiplier)
	FGameplayAttributeData MedKitSelfHealSpeedMultiplier;
	UFUNCTION()
	void OnRep_MedKitSelfHealSpeedMultiplier(const FGameplayAttributeData& OldValue);
	
public:
	ATTRIBUTE_ACCESSORS(UMedkitAttributeSet, MedKitHealSpeedMultiplier)
	ATTRIBUTE_ACCESSORS(UMedkitAttributeSet, MedKitSelfHealSpeedMultiplier)
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
private:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
};
