// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DBDBlueprintFunctionLibrary.generated.h"

class UDBDAbilitySystemComponent;
struct FGameplayTag;
UENUM()
enum class EBaseConfirmType : uint8
{
	Yes,
	No,
};
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDBDBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static UDBDAbilitySystemComponent* NativeGetAbilitySystemComponentFromActor(AActor* Actor);
	
	UFUNCTION(BlueprintCallable, Category="FunctionLibrary")
	static void AddUniqueTagToActor(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category="FunctionLibrary")
	static void RemoveTagFromActor(AActor* Actor, FGameplayTag Tag);

	static bool NativeActorHasTag(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category="FunctionLibrary",
		meta=(DisplayName="Actor Has Tag", ExpandEnumAsExecs = "OutType"))
	static void BP_HasTag(AActor* Actor, FGameplayTag Tag, EBaseConfirmType& OutType);
};
