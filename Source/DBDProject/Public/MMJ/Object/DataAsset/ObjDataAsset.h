// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Engine/DataAsset.h"
#include "ObjDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FObjGEStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> GameplayEffect;

	UPROPERTY(EditAnywhere)
	bool bRemoveWhenFinish = true;
};


/**
 * 
 */
UCLASS()
class DBDPROJECT_API UObjDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, Category = "InitialGEs")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;

	// 진행도 상승 GE (발전기 : 수리이펙트, 갈고리 : 출혈?, 문 : 가동 등등)
	UPROPERTY(EditDefaultsOnly, Category = "ActiveGEs")
	TSubclassOf<UGameplayEffect> ActivateEffect;

	// 진행도 상승 후 추가되는 GE
	UPROPERTY(EditDefaultsOnly, Category = "ActiveGEs")
	TArray<FObjGEStruct> ActiveAdditionalEffects;

	// 진행도 하락 GE (발전기 : 손상, 갈고리 : 파괴공작 등등)
	UPROPERTY(EditDefaultsOnly, Category = "DestroyGEs")
	TSubclassOf<UGameplayEffect> DestroyEffect;

	// 진행도 하락 후 추가되는 GE
	UPROPERTY(EditDefaultsOnly, Category = "DestroyGEs")
	TArray<FObjGEStruct> DestroyAdditionalEffects;

	// 진행도 완료 GE
	UPROPERTY(EditDefaultsOnly, Category = "CompleteGEs")
	TSubclassOf<UGameplayEffect> CompleteEffect;

	// 진행도 완료 후 추가되는 GE
	UPROPERTY(EditDefaultsOnly, Category = "CompleteGEs")
	TArray<FObjGEStruct> CompleteAdditionalEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "InitalGAs")
	TArray<TSubclassOf<UGameplayAbility>> InitializedAbilities;

	// 진행도 상승 GA
	UPROPERTY(EditDefaultsOnly, Category = "ActivateGA")
	TSubclassOf<UGameplayAbility> ActiveAbility;

	// 진행도 하락 GA
	UPROPERTY(EditDefaultsOnly, Category = "DestroyGA")
	TSubclassOf<UGameplayAbility> DestroyAbility;

	// 스킬체크 이벤트 Success시 적용될 이펙트
	UPROPERTY(EditDefaultsOnly, Category = "SkillCheckResultGEs")
	TArray<FObjGEStruct> SkillCheckSuccessEffects;

	// 스킬체크 이벤트 Success시 적용될 Cue의 태그
	UPROPERTY(EditDefaultsOnly, Category = "SkillCheckResultGC")
	FGameplayTag SkillCheckSuccessGCTag;

	// 스킬체크 이벤트 Fail시 적용될 이펙트
	UPROPERTY(EditDefaultsOnly, Category = "SkillCheckResultGEs")
	TArray<FObjGEStruct> SkillCheckFailureEffects;

	// 스킬체크 이벤트 Fail시 적용될 Cue의 태그
	UPROPERTY(EditDefaultsOnly, Category = "SkillCheckResultGC")
	FGameplayTag SkillCheckFailureGCTag;
};
