// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "ObjFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UObjFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static bool ActorHasGameplayTag(AActor* Actor, FGameplayTag Tag);

	static UAbilitySystemComponent* NativeGetAbilitySystemComponent(AActor* Actor);


	// 상호작용 시 액터가 어디붙어있는지 확인용도
	static FGameplayTag ComputeInteractDirection(const AActor* Object, const AActor* Interactor);

	// 캐릭터가 생존자인지 살인마인지 판단 해서 Enum반환
	static EPlayerRole GetPlayerRole(const AActor* Actor);

	// 캐릭터가 생존자인지?
	static bool IsSurvivor(const AActor* Actor);

	// 캐릭터가 살인마인지?
	static bool IsKiller(const AActor* Actor);

	static float GetStaticCooldownDurationForAbility(const class UGameplayAbility* Ability);
	static float GetStaticCostForAbility(const class UGameplayAbility* Ability);
};
