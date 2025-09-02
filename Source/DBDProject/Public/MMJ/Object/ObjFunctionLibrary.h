// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
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

	static float GetStaticCooldownDurationForAbility(const class UGameplayAbility* Ability);
	static float GetStaticCostForAbility(const class UGameplayAbility* Ability);

};
