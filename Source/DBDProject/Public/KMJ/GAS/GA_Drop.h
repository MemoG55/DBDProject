// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KMJ/GAS/KillerGameplayAbility.h"
#include "GA_Drop.generated.h"

class ASurvivorCharacter;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Drop : public UKillerGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetSurvivorGAClearAndDetach();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* TPVDropMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* FPVDropMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* SurvivorDropMontage;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable)
	void OnDrop();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ASurvivorCharacter* CarriedSurvivor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* MontageToPlay;
protected:
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
