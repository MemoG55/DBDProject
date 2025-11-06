// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KMJ/GAS/GA_Locker_Killer.h"
#include "GA_Locker_Huntress.generated.h"

class AKillerHuntress;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Locker_Huntress : public UGA_Locker_Killer
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	UFUNCTION(BlueprintCallable, Category="Ability")
	void PlayMontage(UAnimMontage* Montage);
protected:
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	//Result3. Refill Axe
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="GA_Locker", meta=(AllowPrivateAccess=true))
	UAnimMontage* FPVRefillMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="GA_Locker", meta=(AllowPrivateAccess=true))
	UAnimMontage* TPVRefillMontage;

private:
	UAnimMontage* MontageToPlay = nullptr;
	AKillerHuntress* Huntress = nullptr;
};
