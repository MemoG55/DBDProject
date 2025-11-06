// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/GA/SurvivorInteractionAbility.h"
#include "GA_SelfCare.generated.h"

enum class ESkillCheckResult : uint8;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_SelfCare : public USurvivorInteractionAbility
{
	GENERATED_BODY()
public:
	UGA_SelfCare();
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	float HealInterval = 0.1f;
public:

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;


	virtual void Server_SendSkillCheckResult_Implementation(ESkillCheckResult Result) override;

private:
	FTimerHandle HealTickTimerHandle;
	void Heal();
	FDelegateHandle OnHealProgressChangedHandle;
	void OnHealProgressChanged(const FOnAttributeChangeData& Data);
	
};
