// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/SurvivorGameplayAbility.h"
#include "GA_Survivor_Crouch.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Survivor_Crouch : public USurvivorGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_Survivor_Crouch();

protected:
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                           const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, Category = "GA_Survivor_Crouch")
	TSubclassOf<UGameplayEffect> ChangeSpeedOnCrouchEffect;

	FActiveGameplayEffectHandle CrouchEffectHandle;
};
