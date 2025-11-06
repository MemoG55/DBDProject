// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/GA/SurvivorInteractionAbility.h"
#include "GA_Survivor_HealOther.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Survivor_HealOther : public USurvivorInteractionAbility
{
	GENERATED_BODY()
	
	UPROPERTY()
	ASurvivorCharacter* CachedOtherSurvivor;
public:
	UGA_Survivor_HealOther();
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void Server_SendSkillCheckResult_Implementation(ESkillCheckResult Result) override;

	FTimerHandle HealWidgetTimerHandle;
	void UpdateProgressPercentage();

	virtual void OnSkillCheckBad() override;

};
