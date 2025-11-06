// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DBDEndGameSubsystem.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndGameStartDelegate);

UCLASS()
class DBDPROJECT_API UDBDEndGameSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	// EscapeTimer 시작
	void StartEscapeTimer();

	// 타이머 속도 조절
	void SetTimerSlow(bool bIsSlowCond);

	UPROPERTY()
	float EscapeDuration = 120.f;

	FEndGameStartDelegate OnEndGameStart;
private:
	UPROPERTY()
	FTimerHandle EscapeTimer;

	UPROPERTY()
	float RemainingTime = 0.f;

	// 타이머가 느리게 흐르는지?
	UPROPERTY()
	bool bIsSlow = false;
	
	// 일반적인 타이머 속도
	UPROPERTY()
	float NormalTimerSpeed = 0.1f;

	// 느려진 상태의 타이머 속도
	UPROPERTY()
	float SlowTimerSpeed = 0.05f;
	
	// EscapeTimer Tick
	void TickEscapeTimer();
	
	
};
