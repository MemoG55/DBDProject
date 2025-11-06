// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GA_Active.h"
#include "GA_Pallet.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Pallet : public UGA_Active
{
	GENERATED_BODY()
public:
	UGA_Pallet();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	UPROPERTY(EditAnywhere)
	UAnimMontage* FallGroundMontage;

	UPROPERTY(EditAnywhere)
	UAnimMontage* PullUpMontage;
};
