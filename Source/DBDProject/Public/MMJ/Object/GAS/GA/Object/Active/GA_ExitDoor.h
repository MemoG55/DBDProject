// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GA_Active.h"
#include "GA_ExitDoor.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_ExitDoor : public UGA_Active
{
	GENERATED_BODY()
public:
	UGA_ExitDoor();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual void TaskFunction() override;

	virtual void ExecuteTaskByEvent(FGameplayEventData Data) override;

private:
	UFUNCTION()
	void MontagePlayDelegate();

	UFUNCTION()
	void MontageStopDelegate();
};


