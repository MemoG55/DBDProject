// Fill out your copyright notice in the Description page of Project Settings.
// TODO: 베이스 어빌리티로 전환
#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/GA/SurvivorInteractionAbility.h"
#include "JMS/GAS/SurvivorGameplayAbility.h"
#include "GA_SurvivorOpenExitDoor.generated.h"

class AObj_ExitDoor;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_SurvivorOpenExitDoor : public USurvivorInteractionAbility
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* StartMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* LoopMontage;
public:
	UGA_SurvivorOpenExitDoor();
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData);
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
protected:
	
	UFUNCTION()
	void PlayLoopMontage();
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	

private:
	TObjectPtr<UInteractorComponent> CachedInteractorComponent;
	TObjectPtr<AObj_ExitDoor> CachedExitDoor; 
};
