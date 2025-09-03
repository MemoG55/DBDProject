// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_KillerInput.generated.h"


class UInputAction;
class UInputMappingContext;

UENUM(BlueprintType)
enum class EKillerAbilityInputID : uint8
{
	None		UMETA(DisplayName = "None"),
};
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

	//살인마 기본 공격-왼쪽 마우스 키
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* IA_Attack;

	//살인마 고유 능력-오른쪽 마우스 키
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* IA_Skill;

	//상호작용(생존자 들기, 판자 부수기, 창틀 넘기, 벽 부수기, 비상탈출구 닫기....)
	//Space
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* IA_Interact;
	
	//생존자 내려놓기-R키
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* IA_Drop;

	//생존자 즉처-Q키
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* IA_Kill;
};