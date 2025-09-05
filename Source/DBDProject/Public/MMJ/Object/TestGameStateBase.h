// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/GameStateBase.h"
#include "GAS/ObjAbilitySystemComponent.h"
#include "GAS/ObjAttributeSet.h"
#include "TestGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API ATestGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	ATestGameStateBase();

	
	
protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameClearCondition")
	TArray<ADBDObject*> Generators;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameClearCondition")
	TArray<ADBDObject*> ExitDoors;
	
	UFUNCTION()
	void GetRequiredGeneratorCount();

	UFUNCTION()
	void CheckGeneratorState();
};
