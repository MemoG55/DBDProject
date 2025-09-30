// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "KillerAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWalkingSpeedDelegate, float, NewWalkingSpeed);

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class DBDPROJECT_API UKillerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UKillerAttributeSet();
	
	//이동 속도
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_WalkingSpeed)
	FGameplayAttributeData WalkingSpeed;
	ATTRIBUTE_ACCESSORS(UKillerAttributeSet, WalkingSpeed);
	UFUNCTION()
	virtual void OnRep_WalkingSpeed(const FGameplayAttributeData& OldValue) const;
	UFUNCTION(BlueprintPure)
	float SetCurrentWalkingSpeed(float NewWalkingSpeed);
	
	UPROPERTY(BlueprintAssignable, Category = "Axe")
	FWalkingSpeedDelegate OnWalkingSpeedChanged;
	UFUNCTION(BlueprintPure)
	float GetCurrentWalkingSpeed() const{return WalkingSpeed.GetCurrentValue();};
	
	
	//살인마 기절 시간(애니메이션 재생 Rate)
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_StunRate)
	FGameplayAttributeData StunRate;
	ATTRIBUTE_ACCESSORS(UKillerAttributeSet, StunRate);
	UFUNCTION()
	virtual void OnRep_StunRate(const FGameplayAttributeData& OldValue) const;

	//생존자 드는 시간(애니메이션 재생 Rate)
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_PickUpSpeedRate)
	FGameplayAttributeData PickUpSpeedRate;
	ATTRIBUTE_ACCESSORS(UKillerAttributeSet, PickUpSpeedRate);
	UFUNCTION()
	virtual void OnRep_PickUpSpeedRate(const FGameplayAttributeData& OldValue) const;

	//살인마 공포 범위
	//4.6m/s -> 32m | 4.4m/s -> 24m
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_TerrorRadiusRange)
	FGameplayAttributeData TerrorRadiusRange;
	ATTRIBUTE_ACCESSORS(UKillerAttributeSet, TerrorRadiusRange);
	UFUNCTION()
	virtual void OnRep_TerrorRadiusRange(const FGameplayAttributeData& OldValue) const;

	//판자 부수기 속도(애니메이션 재생 Rate)
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_DestroyPalletRate)
	FGameplayAttributeData DestroyPalletRate;
	ATTRIBUTE_ACCESSORS(UKillerAttributeSet, DestroyPalletRate);
	UFUNCTION()
	virtual void OnRep_DestroyPalletRate(const FGameplayAttributeData& OldValue) const;

	//발전기 부수기 속도
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_DamageGeneratorRate)
	FGameplayAttributeData DamageGeneratorRate;
	ATTRIBUTE_ACCESSORS(UKillerAttributeSet, DamageGeneratorRate);
	UFUNCTION()
	virtual void OnRep_DamageGeneratorRate(const FGameplayAttributeData& OldValue) const;

	//일반 공격 후 경직(애니메이션 재생 Rate)
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_AfterAttackRate)
	FGameplayAttributeData AfterAttackRate;
	ATTRIBUTE_ACCESSORS(UKillerAttributeSet, AfterAttackRate);
	UFUNCTION()
	virtual void OnRep_AfterAttackRate(const FGameplayAttributeData& OldValue) const;
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};