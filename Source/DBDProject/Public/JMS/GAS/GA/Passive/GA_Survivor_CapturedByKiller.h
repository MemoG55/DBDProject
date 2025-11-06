// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/SurvivorGameplayAbility.h"
#include "JMS/GAS/GA/SurvivorPassiveAbility.h"
#include "Shared/DBDStruct.h"
#include "GA_Survivor_CapturedByKiller.generated.h"

class AKillerCharacter;
enum class ESkillCheckResult : uint8;
/**
 *
 */
UCLASS()
class DBDPROJECT_API UGA_Survivor_CapturedByKiller : public USurvivorPassiveAbility
{
	GENERATED_BODY()

public:
	UGA_Survivor_CapturedByKiller();
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
	UPROPERTY()
	TObjectPtr<UInteractableComponent> CachedInteractableComponent;
	UPROPERTY()
	TObjectPtr<AKillerCharacter> CachedKillerCharacter;
	FMotionWarpingInfo PickUpInMotionWarpingInfo;
	TArray<FMotionWarpingInfo> TargetInfoArray;
};