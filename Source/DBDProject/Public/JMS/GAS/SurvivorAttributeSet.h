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

// DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCurrentAttributeChangedDelegate, float, Percent);

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
	UPROPERTY(ReplicatedUsing=OnRep_SprintSpeed)
	FGameplayAttributeData SprintSpeed;
	UPROPERTY(ReplicatedUsing=OnRep_CrouchSpeed)
	FGameplayAttributeData CrouchSpeed;
	UPROPERTY(ReplicatedUsing=OnRep_CrawlSpeed)
	FGameplayAttributeData CrawlSpeed;
	UPROPERTY(ReplicatedUsing=OnRep_InteractSpeed_Generator)
	FGameplayAttributeData InteractSpeed_Generator;
	UPROPERTY(ReplicatedUsing=OnRep_InteractSpeed_ExitDoor)
	FGameplayAttributeData InteractSpeed_ExitDoor;
	UPROPERTY(ReplicatedUsing=OnRep_InteractSpeed_Chest)
	FGameplayAttributeData InteractSpeed_Chest;
	UPROPERTY(ReplicatedUsing=OnRep_InteractSpeed_TotemCleansing)
	FGameplayAttributeData InteractSpeed_TotemCleansing;
	UPROPERTY(ReplicatedUsing=OnRep_HealSpeed)
	FGameplayAttributeData HealSpeed;
	UPROPERTY(ReplicatedUsing=OnRep_HookSabotageSpeed)
	FGameplayAttributeData HookSabotageSpeed;
	UPROPERTY(ReplicatedUsing=OnRep_RescueSpeed)
	FGameplayAttributeData RescueSpeed;
	UPROPERTY(ReplicatedUsing=OnRep_SkillCheckFrequency)
	FGameplayAttributeData SkillCheckFrequency;
	UPROPERTY(ReplicatedUsing=OnRep_QuickActionSoundVolume)
	FGameplayAttributeData QuickActionSoundVolume;
	UPROPERTY(ReplicatedUsing=OnRep_CurrentItemCharge)
	FGameplayAttributeData CurrentItemCharge;
	UPROPERTY(ReplicatedUsing=OnRep_MaxItemCharge)
	FGameplayAttributeData MaxItemCharge;

public:
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, MaxHookHP)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, HookHP)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, MaxDyingHP)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, DyingHP)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, MaxHealProgress)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, HealProgress)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, MovementSpeed)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, SprintSpeed)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, CrouchSpeed)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, CrawlSpeed)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, InteractSpeed_Generator)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, InteractSpeed_ExitDoor)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, InteractSpeed_Chest)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, InteractSpeed_TotemCleansing)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, HealSpeed)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, HookSabotageSpeed)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, RescueSpeed)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, SkillCheckFrequency)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, QuickActionSoundVolume)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, CurrentItemCharge)
	ATTRIBUTE_ACCESSORS(USurvivorAttributeSet, MaxItemCharge)

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
	void OnRep_SprintSpeed(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_CrouchSpeed(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_CrawlSpeed(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_InteractSpeed_Generator(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_InteractSpeed_ExitDoor(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_InteractSpeed_Chest(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_InteractSpeed_TotemCleansing(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_HealSpeed(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_HookSabotageSpeed(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_RescueSpeed(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_SkillCheckFrequency(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_QuickActionSoundVolume(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_CurrentItemCharge(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxItemCharge(const FGameplayAttributeData& OldValue);

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

public:
	// UPROPERTY()
	// FOnCurrentAttributeChangedDelegate OnCurrentItemChargeChanged;
};
