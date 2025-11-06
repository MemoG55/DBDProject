// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ToolboxAttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
UCLASS()
class DBDPROJECT_API UToolboxAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
private:
	UPROPERTY(ReplicatedUsing=OnRep_ToolboxRepairSpeedMultiplier)
	FGameplayAttributeData ToolboxRepairSpeedMultiplier;
	UFUNCTION()
	void OnRep_ToolboxRepairSpeedMultiplier(const FGameplayAttributeData& OldValue);

	UPROPERTY(ReplicatedUsing=OnRep_ToolboxSabotageSpeedMultiplier)
	FGameplayAttributeData ToolboxSabotageSpeedMultiplier;
	UFUNCTION()
	void OnRep_ToolboxSabotageSpeedMultiplier(const FGameplayAttributeData& OldValue);
public:
	ATTRIBUTE_ACCESSORS(UToolboxAttributeSet, ToolboxRepairSpeedMultiplier)
	ATTRIBUTE_ACCESSORS(UToolboxAttributeSet, ToolboxSabotageSpeedMultiplier)
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
private:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	
	
	
	
};
