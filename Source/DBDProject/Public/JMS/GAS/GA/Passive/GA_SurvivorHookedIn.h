// Fill out your copyright notice in the Description page of Project Settings.
// TODO: 애니메이션 오프셋이 달라서 중간과정 애니메이션을 적용할 수 없음 - 개선
#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/SurvivorGameplayAbility.h"
#include "JMS/GAS/GA/SurvivorPassiveAbility.h"
#include "GA_SurvivorHookedIn.generated.h"

class AObj_Hook;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_SurvivorHookedIn : public USurvivorPassiveAbility
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* StartInMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* StartOutMontage;


	TObjectPtr<AObj_Hook> CachedHook;


public:
	UGA_SurvivorHookedIn();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
protected:
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
	// TODO: 중간과정 애니메이션 개선 필요 - 클라이언트에서는 Hook에 접근이 안돼서 애니메이션이 실행되지 않음
	// UFUNCTION()
	// void PlayStartOutMontage();
	
	
};
