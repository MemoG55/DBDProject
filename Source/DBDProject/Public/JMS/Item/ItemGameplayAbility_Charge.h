// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/GA/SurvivorInteractionAbility.h"
#include "ItemGameplayAbility_Charge.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UItemGameplayAbility_Charge : public USurvivorInteractionAbility
{
	GENERATED_BODY()
public:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	// void OnTimerTick();
	UPROPERTY(EditDefaultsOnly)
	float ChargeConsumptionPerSecond = 3.0f;
protected:
	UPROPERTY(EditDefaultsOnly, Category = "GE")
	TSubclassOf<UGameplayEffect> ChargeConsumptionEffect;
	UPROPERTY()
	FActiveGameplayEffectHandle ChargeConsumptionEffectHandle;
	void OnCurrentItemChargeChanged(const FOnAttributeChangeData& OnAttributeChangeData);
	FDelegateHandle ChargeChangedDelegateHandle;
};
