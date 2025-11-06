// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KMJ/GAS/KillerGameplayAbility.h"
#include "GA_Skill.generated.h"

class AKillerHuntress;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Skill : public UKillerGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_Skill();
	void StartChargingAxe();
	void UpdateChargingAxe();
	void UpdateAxeSpeed(float NewSpeed);
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	
protected:
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(BlueprintReadWrite, Category="GA_Skill")
	AKillerHuntress* Huntress;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GA_Skill")
	UAnimMontage* FPVThrowInAndIdleMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GA_Skill")
	UAnimMontage* TPVThrowInAndIdleMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GA_Skill")
	UAnimMontage* FPVThrowAndCooldownMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GA_Skill")
	UAnimMontage* TPVThrowAndCooldownMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GA_Skill")
	bool bIsCoolDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GA_Skill")
	float CurrentSpeed;
	FTimerHandle ChargeTimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="GA_Skill")
	float CurrentChargeTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="GA_Skill")
	float MinChargingTime;
	UPROPERTY(EditDefaultsOnly, Category="GA_Skill")
	float MaxChargingTime;
	UPROPERTY(EditDefaultsOnly, Category="GA_Skill")
	float MinChargingSpeed;
	UPROPERTY(EditDefaultsOnly, Category="GA_Skill")
	float MaxChargingSpeed;
};
