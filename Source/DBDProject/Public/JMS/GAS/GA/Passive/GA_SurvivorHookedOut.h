// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/GA/SurvivorPassiveAbility.h"
#include "GA_SurvivorHookedOut.generated.h"

class AObj_Hook;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_SurvivorHookedOut : public USurvivorPassiveAbility
{
	GENERATED_BODY()
public:
	UGA_SurvivorHookedOut();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
protected:
	AObj_Hook* CachedHook;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* StartOutMontage;
	
};
