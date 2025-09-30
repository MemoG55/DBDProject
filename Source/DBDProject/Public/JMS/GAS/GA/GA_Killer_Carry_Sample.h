// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KMJ/GAS/GA_Carry.h"
#include "KMJ/GAS/KillerGameplayAbility.h"
#include "GA_Killer_Carry_Sample.generated.h"

class ASurvivorCharacter;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Killer_Carry_Sample : public UGA_Carry
{
	GENERATED_BODY()
public:
	UGA_Killer_Carry_Sample();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	FName AttachSocketName;
private:
protected:
	UFUNCTION()
	void PlayLoopMontage();
	UFUNCTION()
	void AttachSurvivorCharacterToKiller(FGameplayEventData Payload);
	UFUNCTION()
	AKillerCharacter* GetOwningKillerCharacter();
};
