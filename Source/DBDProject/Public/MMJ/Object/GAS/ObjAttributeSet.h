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
	// 아래 함수들 실행 순서
	// PreGameplayEffectExecute -> PreAttributeChange -> PostAttributeChange -> PostGameplayEffectExecute
	
	// Effect가 실행되기 직전 (가장먼저 호출)
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;

	// Effect가 실행된 후 (가장마지막 호출)
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	// Attribute값이 변경되기 직전 호출(최종 변경값 지정 가능)
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// Attribute값이 변경된 후 호출(NewValue는 변경된 값을 복사한 값)
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(ReplicatedUsing = OnRep_MaxTask)
	FGameplayAttributeData MaxTask;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentTask)
	FGameplayAttributeData CurrentTask;

	UPROPERTY(ReplicatedUsing = OnRep_RecoverTask)
	FGameplayAttributeData RecoverTask;

	// 손상도(갈고리 등 파괴되었다가 수리되기 위한 타이머 용도로)
	UPROPERTY(ReplicatedUsing = OnRep_MaxDamage)
	FGameplayAttributeData MaxDamage;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentDamage);
	FGameplayAttributeData CurrentDamage;

	UFUNCTION()
	void OnRep_MaxTask(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_CurrentTask(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxDamage(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_CurrentDamage(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_RecoverTask(const FGameplayAttributeData& OldValue);

public:
	ATTRIBUTE_ACCESSORS(UObjAttributeSet, MaxTask)
	ATTRIBUTE_ACCESSORS(UObjAttributeSet, CurrentTask)
	ATTRIBUTE_ACCESSORS(UObjAttributeSet, MaxDamage)
	ATTRIBUTE_ACCESSORS(UObjAttributeSet, CurrentDamage)
	ATTRIBUTE_ACCESSORS(UObjAttributeSet, RecoverTask)
};
