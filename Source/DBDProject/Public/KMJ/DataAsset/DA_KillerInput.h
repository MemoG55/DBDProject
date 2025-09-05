// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_KillerInput.generated.h"

class DBDEnum;
enum class EKillerAbilityInputID : uint8;
class UInputAction;
class UInputMappingContext;


/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDA_KillerInput : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta=(AllowPrivateAccess = "true"))
	TMap<EKillerAbilityInputID, class UInputAction*> GameplayAbilityInputActions;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	int32 InputMappingContextPriority;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* IA_Move;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* IA_Look;
};