// Fill out your copyright notice in the Description page of Project Settings.
// 생존자가 탈출 시 물리연산을 없애고 Hidden처리합니다.
// TODO: 탈출 화면 애니메이션 실행
#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/SurvivorGameplayAbility.h"
#include "JMS/GAS/GA/SurvivorPassiveAbility.h"
#include "GA_SurvivorEscape.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_SurvivorEscape : public USurvivorPassiveAbility
{
	GENERATED_BODY()

public:
	UGA_SurvivorEscape();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
};
