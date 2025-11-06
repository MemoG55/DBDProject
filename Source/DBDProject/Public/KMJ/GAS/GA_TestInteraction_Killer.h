// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KMJ/GAS/KillerGameplayAbility.h"
#include "GA_TestInteraction_Killer.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_TestInteraction_Killer : public UKillerGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_TestInteraction_Killer();
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							  const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							   const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
							bool bWasCancelled) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "TestAbility")
	bool bIsHoldType = false;

	UPROPERTY()
	TObjectPtr<UInteractorComponent> CachedInteractorComponent;
};
