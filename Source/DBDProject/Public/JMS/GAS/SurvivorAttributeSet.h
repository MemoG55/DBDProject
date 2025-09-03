// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "SurvivorAttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class DBDPROJECT_API USurvivorAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

private:
	UPROPERTY(ReplicatedUsing=OnRep_HookHP)
	FGameplayAttributeData HookHP;
	UPROPERTY(ReplicatedUsing=OnRep_DyingHP)
	FGameplayAttributeData DyingHP;
	UPROPERTY(ReplicatedUsing=OnRep_HealProgress)
	FGameplayAttributeData HealProgress;
	UPROPERTY(ReplicatedUsing=OnRep_MovementSpeed)
	FGameplayAttributeData MovementSpeed;
	UPROPERTY(ReplicatedUsing=OnRep_GeneratorRepairSpeed)
	FGameplayAttributeData GeneratorRepairSpeed;

public:
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, HookHP)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, DyingHP)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, HealProgress)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, MovementSpeed)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, GeneratorRepairSpeed)
	
private:
	UFUNCTION()
	void OnRep_HookHP(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_DyingHP(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_HealProgress(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MovementSpeed(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_GeneratorRepairSpeed(const FGameplayAttributeData& OldValue);
public:
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
