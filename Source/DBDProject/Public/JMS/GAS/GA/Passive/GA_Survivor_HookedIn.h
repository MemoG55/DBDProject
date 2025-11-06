// Fill out your copyright notice in the Description page of Project Settings.
// TODO: 애니메이션 오프셋이 달라서 중간과정 애니메이션을 적용할 수 없음 - 개선
#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/SurvivorGameplayAbility.h"
#include "JMS/GAS/GA/SurvivorPassiveAbility.h"
#include "GA_Survivor_HookedIn.generated.h"

struct FMotionWarpingInfo;
class AObj_Hook;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Survivor_HookedIn : public USurvivorPassiveAbility
{
	GENERATED_BODY()
public:
	UGA_Survivor_HookedIn();
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
	UPROPERTY()
	ASurvivorCharacter* CachedSurvivor;
	UFUNCTION()
	void Rescued(FGameplayEventData Data);

	FTimerHandle HookWidgetTimerHandle;
	void UpdateProgressPercentage();
};
