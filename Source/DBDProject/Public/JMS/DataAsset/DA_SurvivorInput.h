// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_SurvivorInput.generated.h"
enum class ESurvivorAbilityInputID : uint8;
class UInputAction;
class UInputMappingContext;


UCLASS()
class DBDPROJECT_API UDA_SurvivorInput : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta=(AllowPrivateAccess = "true"))
	TMap<ESurvivorAbilityInputID, class UInputAction*> GameplayAbilityInputActions;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	int32 InputMappingContextPriority;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* IA_Move;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* IA_Look;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* IA_Crouch;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* IA_UseItem;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* IA_DropItem;
};
