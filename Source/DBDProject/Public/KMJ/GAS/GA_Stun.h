// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KMJ/GAS/KillerGameplayAbility.h"
#include "GA_Stun.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Stun : public UKillerGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
protected:
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Killer", meta=(AllowPrivateAccess=true))
	UAnimMontage* StunMontageFPV;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Killer", meta=(AllowPrivateAccess=true))
	UAnimMontage* StunMontageTPV;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Killer", meta=(AllowPrivateAccess=true))
	UAnimMontage* MontageToPlay;

	
	
};
