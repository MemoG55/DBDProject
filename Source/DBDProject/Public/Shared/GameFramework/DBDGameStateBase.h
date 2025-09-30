// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/GameStateBase.h"
#include "../../MMJ/Object/GAS/ObjAbilitySystemComponent.h"
#include "../../MMJ/Object/GAS/ObjAttributeSet.h"
#include "DBDGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEscapeTimerBeginDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEscapeTimerEndDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEscapeTimerDelegate, float, NewValue);

/**
 * 
 */
UCLASS()
class DBDPROJECT_API ADBDGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	ADBDGameStateBase();

	FOnEscapeTimerBeginDelegate OnEscapeTimerBegin;
	FOnEscapeTimerEndDelegate OnEscapeTimerEnd;
	FOnEscapeTimerDelegate OnEscapeTimer;
	

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	// 탈출 타이머 발동 시간
	UPROPERTY(ReplicatedUsing = OnRep_RemainingEscapeTime)
	float RemainingEscapeTime = 120.f;

	UPROPERTY()
	float MaxEscapeTime = 120.f;

	// 탈출 타이머 실행주기
	UPROPERTY()
	float EscapeTimerInterval = 0.1f;

	// 탈출 타이머
	UPROPERTY(ReplicatedUsing = OnRep_EscapeTimer)
	FTimerHandle EscapeTimer;
	
public:
	UFUNCTION(BlueprintCallable)
	float GetMaxEscapeTime();
	
	UFUNCTION()
	void SetEscapeTimer();

	UFUNCTION()
	void TickEscapeTimer();

	// 탈출 타이머의 남은 시간을 리플리케이트
	UFUNCTION()
	void OnRep_RemainingEscapeTime();

	UFUNCTION()
	void OnRep_EscapeTimer();

	UPROPERTY(ReplicatedUsing = OnRep_bIsGameEnded)
	bool bIsGameEnded;

	UFUNCTION()
	void SetGameEnd(bool Result);

	UFUNCTION()
	void OnRep_bIsGameEnded();

	UFUNCTION(Client, Reliable)
	void MoveToEndGameLevel();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UUserWidget* EndGameWidget;
	
protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameClearCondition")
	TArray<ADBDObject*> Generators;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameClearCondition")
	TArray<ADBDObject*> ExitDoors;
	
	UFUNCTION()
	int32 GetRequiredGeneratorCount();

	UFUNCTION()
	void CheckGeneratorState();

	UFUNCTION()
	int32 GetSurvivorCount();

private:
	// 수리된 발전기 수량
	UPROPERTY()
	int32 RepairGeneratorCount;

public:
	UFUNCTION()
	int32 GetRepairGeneratorCount();
};

