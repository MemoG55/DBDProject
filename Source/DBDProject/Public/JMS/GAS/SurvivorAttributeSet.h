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
	UPROPERTY(ReplicatedUsing=OnRep_MaxHookHP)
	FGameplayAttributeData MaxHookHP;
	UPROPERTY(ReplicatedUsing=OnRep_HookHP)
	FGameplayAttributeData HookHP;
	UPROPERTY(ReplicatedUsing=OnRep_MaxDyingHP)
	FGameplayAttributeData MaxDyingHP;
	UPROPERTY(ReplicatedUsing=OnRep_DyingHP)
	FGameplayAttributeData DyingHP;
	UPROPERTY(ReplicatedUsing=OnRep_MaxHealProgress)
	FGameplayAttributeData MaxHealProgress;
	UPROPERTY(ReplicatedUsing=OnRep_HealProgress)
	FGameplayAttributeData HealProgress;
	UPROPERTY(ReplicatedUsing=OnRep_MovementSpeed)
	FGameplayAttributeData MovementSpeed;
	UPROPERTY(ReplicatedUsing=OnRep_GeneratorRepairSpeed)
	FGameplayAttributeData GeneratorRepairSpeed;
	UPROPERTY(ReplicatedUsing=OnRep_HealSpeed)
	FGameplayAttributeData HealSpeed;
	UPROPERTY(ReplicatedUsing=OnRep_SkillCheckFrequency)
	FGameplayAttributeData SkillCheckFrequency;

public:
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, MaxHookHP)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, HookHP)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, MaxDyingHP)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, DyingHP)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, MaxHealProgress)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, HealProgress)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, MovementSpeed)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, GeneratorRepairSpeed)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, HealSpeed)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, SkillCheckFrequency)
	
private:
	UFUNCTION()
	void OnRep_MaxHookHP(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_HookHP(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxDyingHP(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_DyingHP(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxHealProgress(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_HealProgress(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MovementSpeed(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_GeneratorRepairSpeed(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_HealSpeed(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_SkillCheckFrequency(const FGameplayAttributeData& OldValue);
public:
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	private:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
