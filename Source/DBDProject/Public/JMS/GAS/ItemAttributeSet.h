// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ItemAttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class DBDPROJECT_API UItemAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
private:
	UPROPERTY(ReplicatedUsing=OnRep_CurrentCharge)
	FGameplayAttributeData CurrentCharge;
	UFUNCTION()
	void OnRep_CurrentCharge(const FGameplayAttributeData& OldValue);

	UPROPERTY(ReplicatedUsing=OnRep_MaxCharge)
	FGameplayAttributeData MaxCharge;
	UFUNCTION()
	void OnRep_MaxCharge(const FGameplayAttributeData& OldValue);
public:
	ATTRIBUTE_ACCESSORS(UItemAttributeSet, CurrentCharge)
	ATTRIBUTE_ACCESSORS(UItemAttributeSet, MaxCharge)
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
private:
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	
};
