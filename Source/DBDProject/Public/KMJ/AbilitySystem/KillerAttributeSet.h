// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "KillerAttributeSet.generated.h"

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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Killer")
	FGameplayAttributeData WalkingSpeed;
	ATTRIBUTE_ACCESSORS(UKillerAttributeSet, WalkingSpeed);

	//살인마 기절 시간(애니메이션 재생 Rate)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Killer")
	FGameplayAttributeData StunRate;
	ATTRIBUTE_ACCESSORS(UKillerAttributeSet, StunRate);

	//생존자 드는 시간(애니메이션 재생 Rate)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Killer")
	FGameplayAttributeData PickUpSpeedRate;
	ATTRIBUTE_ACCESSORS(UKillerAttributeSet, PickUpSpeedRate);

	//살인마 공포 범위
	//4.6m/s -> 32m | 4.4m/s -> 24m
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Killer")
	FGameplayAttributeData TerrorRadiusRange;
	ATTRIBUTE_ACCESSORS(UKillerAttributeSet, TerrorRadiusRange);

	//판자 부수기 속도(애니메이션 재생 Rate)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Killer")
	FGameplayAttributeData DestroyPalletRate;
	ATTRIBUTE_ACCESSORS(UKillerAttributeSet, DestroyPalletRate);

	//발전기 부수기 속도
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Killer")
	FGameplayAttributeData DamageGeneratorRange;
	ATTRIBUTE_ACCESSORS(UKillerAttributeSet, DamageGeneratorRange);
};