// Fill out your copyright notice in the Description page of Project Settings.
// TODO: 베이스 어빌리티로 전환
#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/GA/SurvivorInteractionAbility.h"
#include "JMS/GAS/SurvivorGameplayAbility.h"
#include "GA_Survivor_OpenExitDoor.generated.h"

class AObj_ExitDoor;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Survivor_OpenExitDoor : public USurvivorInteractionAbility
{
	GENERATED_BODY()
public:
	UGA_Survivor_OpenExitDoor();
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
protected:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

};
