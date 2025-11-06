// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/GA/SurvivorInteractionAbility.h"
#include "GA_Survivor_Rescue.generated.h"

class AObj_Hook;
class AObj_ExitDoor;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Survivor_Rescue : public USurvivorInteractionAbility
{
	GENERATED_BODY()
public:
	UGA_Survivor_Rescue();
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
protected:
	UFUNCTION()
	void OnRescueSucceed();

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
	bool bIsRescueSucceed = false;
	FTimerHandle RescueTimerHandle;
	UPROPERTY()
	ASurvivorCharacter* CachedCapturedSurvivor;

	UFUNCTION(Client, Reliable)
	void Client_StartWidgetUpdate(float AnimDuration, float RescueSpeed);
	
	FTimerHandle RescueWidgetTimerHandle;
	FTimerDelegate RescueWidgetTimerDelegate;
	void UpdateProgressPercentageByDeltaProgress(float DeltaProgress);
};
