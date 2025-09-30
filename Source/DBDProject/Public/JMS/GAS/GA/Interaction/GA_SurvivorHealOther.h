// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/GA/SurvivorInteractionAbility.h"
#include "GA_SurvivorHealOther.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_SurvivorHealOther : public USurvivorInteractionAbility
{
	GENERATED_BODY()
		
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* HealMontage;


	UPROPERTY(EditDefaultsOnly, Category = "GE")
	TSubclassOf<UGameplayEffect> HealGE;

public:
	UGA_SurvivorHealOther();
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData);
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
protected:
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	UFUNCTION()
	void OnSkillCheckEnd(ESkillCheckResult Result);

	UFUNCTION(Server, Reliable)
	void Server_SendSkillCheckResult(ESkillCheckResult Result);

private:
	TObjectPtr<USkillCheckComponent> CachedSkillCheckComponent;
	TObjectPtr<UInteractorComponent> CachedInteractorComponent;
	TObjectPtr<ASurvivorCharacter> CachedSurvivor;
	FTimerHandle SkillCheckTimerHandle;
	void SetSkillCheckTimer(float frequency);
	void PlaySkillCheck();
	void OnSkillCheckInterrupted();
	
	
	
};
