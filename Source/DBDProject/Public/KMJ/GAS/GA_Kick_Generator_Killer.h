// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KMJ/GAS/KillerGameplayAbility.h"
#include "GA_Kick_Generator_Killer.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Kick_Generator_Killer : public UKillerGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_Kick_Generator_Killer();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	
protected:
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Killer", meta=(AllowPrivateAccess=true))
	UAnimMontage* KickMontageFPV;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Killer", meta=(AllowPrivateAccess=true))
	UAnimMontage* KickMontageTPV;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Killer", meta=(AllowPrivateAccess=true))
	UAnimMontage* MontageToPlay;
	
};
