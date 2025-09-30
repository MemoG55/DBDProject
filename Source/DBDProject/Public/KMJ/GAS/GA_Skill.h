// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KMJ/GAS/KillerGameplayAbility.h"
#include "GA_Skill.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Skill : public UKillerGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnPressed();
	
};
