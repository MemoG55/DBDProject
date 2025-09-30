// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Shared/DataAsset/DA_DBDASCData.h"
#include "DA_KillerGameplayAbilities.generated.h"

class UGameplayAbility;
class UGameplayEffect;
enum class EKillerAbilityInputID : uint8;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDA_KillerGameplayAbilities : public UDA_DBDASCData
{
	GENERATED_BODY()
public:
	UDA_KillerGameplayAbilities(const FObjectInitializer& ObjectInitializer);
	/*
	UPROPERTY(EditDefaultsOnly, Category="GEs")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;

	//초기세팅 어빌리티
	UPROPERTY(EditDefaultsOnly, Category="GA")
	TArray<TSubclassOf<UGameplayAbility>> InitializedAbilities;
	*/

	//특수 능력
	UPROPERTY(EditDefaultsOnly, Category="GA")
	TMap<EKillerAbilityInputID, TSubclassOf<UGameplayAbility>> SkillAbilities;

	//기본 능력
	UPROPERTY(EditDefaultsOnly, Category="GA")
	TMap<EKillerAbilityInputID, TSubclassOf<UGameplayAbility>> BaseAbilities;
};
