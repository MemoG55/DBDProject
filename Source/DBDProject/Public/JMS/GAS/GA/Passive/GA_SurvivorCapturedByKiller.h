// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/SurvivorGameplayAbility.h"
#include "JMS/GAS/GA/SurvivorPassiveAbility.h"
#include "GA_SurvivorCapturedByKiller.generated.h"

class AKillerCharacter;
enum class ESkillCheckResult : uint8;
/**
 *
 */
UCLASS()
class DBDPROJECT_API UGA_SurvivorCapturedByKiller : public USurvivorPassiveAbility
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* PickUpInMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* PickUpMontage;

public:
	UGA_SurvivorCapturedByKiller();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
protected:
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	UFUNCTION()
	void PlayPickUpMontage();

private:
	TObjectPtr<UInteractableComponent> CachedInteractableComponent;
	TObjectPtr<AKillerCharacter> CachedKillerCharacter;
};