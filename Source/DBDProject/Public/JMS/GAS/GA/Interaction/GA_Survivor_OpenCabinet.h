// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/GA/SurvivorInteractionAbility.h"
#include "GA_Survivor_OpenCabinet.generated.h"

class AObj_Cabinet;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Survivor_OpenCabinet : public USurvivorInteractionAbility
{
	GENERATED_BODY()
public:
	UGA_Survivor_OpenCabinet();
protected:
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
							bool bWasCancelled) override;
	UFUNCTION(Server, Reliable)
	virtual void Server_GetOut();
private:
	UPROPERTY()
	AObj_Cabinet* CachedCabinet;
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
};
