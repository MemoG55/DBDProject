// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KMJ/GAS/KillerGameplayAbility.h"
#include "GA_Attack.generated.h"

class AKillerHuntress;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Attack : public UKillerGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_Attack();
	void IncreaseSpeed();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GA_Attack",Replicated)
	bool bIsCoolDown;
	

	UFUNCTION(BlueprintCallable, Category="Ability")
	void CallBeforeEndAbility();

	UFUNCTION(BlueprintCallable, Category="Ability")
	void EndAbilityExternally()
	{
		K2_EndAbility();
	}
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category="Ability")
	void PlayMontage(UAnimMontage* Montage);
	
	UFUNCTION()
	void Launch();

	FTimerHandle SpeedIncreaseTimerHandle;
	float Speed;
protected:
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="GA_Attack")
	UAnimMontage* FPVAttackInMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="GA_Attack")
	UAnimMontage* TPVAttackInMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="GA_Attack")
	UAnimMontage* FPVAttackMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="GA_Attack")
	UAnimMontage* TPVAttackMontage;
};
