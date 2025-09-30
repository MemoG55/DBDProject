// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/GAS/GA/DBDGameplayAbility.h"
#include "GA_Shared_Blind.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Shared_Blind : public UDBDGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_Shared_Blind();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
};
