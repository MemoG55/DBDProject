// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ObjAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UObjAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

private:
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	virtual void PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(ReplicatedUsing = OnRep_MaxTask)
	FGameplayAttributeData MaxTask;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentTask)
	FGameplayAttributeData CurrentTask;
	

	UFUNCTION()
	void OnRep_MaxTask(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_CurrentTask(const FGameplayAttributeData& OldValue);

public:
	ATTRIBUTE_ACCESSORS(UObjAttributeSet, MaxTask)
	ATTRIBUTE_ACCESSORS(UObjAttributeSet, CurrentTask)
};
