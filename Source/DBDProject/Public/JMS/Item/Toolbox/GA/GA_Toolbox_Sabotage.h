// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/GA/SurvivorInteractionAbility.h"
#include "JMS/GAS/GA/SurvivorUseItemAbility.h"
#include "GA_Toolbox_Sabotage.generated.h"

class AObj_Hook;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Toolbox_Sabotage : public USurvivorInteractionAbility
{
	GENERATED_BODY()
public:
	UGA_Toolbox_Sabotage();
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData);
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION()
	void OnSabotageSucceed();
private:
	UPROPERTY()
	TObjectPtr<AObj_Hook> CachedHook;

	UPROPERTY(EditDefaultsOnly, Category = "Cost")
	float SabotageCost = 6.0f;

	FTimerHandle SabotageTimerHandle;
	UPROPERTY(EditDefaultsOnly, Category = "GE")
	TSubclassOf<UGameplayEffect> SabotageChargeConsumptionEffect;

	UFUNCTION(Client, Reliable)
	void Client_StartWidgetUpdate(float AnimDuration, float SabotageSpeed);
	
	FTimerHandle SabotageWidgetTimerHandle;
	FTimerDelegate SabotageWidgetTimerDelegate;
	void UpdateProgressPercentageByDeltaProgress(float DeltaProgress);
};
