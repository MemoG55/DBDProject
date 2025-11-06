// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GA_Active.h"
#include "GA_Generator.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Generator : public UGA_Active
{
	GENERATED_BODY()
public:
	UGA_Generator();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void TaskFunction() override;

	virtual void ExecuteGameplayEffectAndCue(FGameplayEventData Data) override;

private:

#pragma region InteractionAnimation:
	UPROPERTY(EditAnywhere, Category = "InteractionAnimation")
	TMap<FGameplayTag, UAnimMontage*> InteractionAnimationsByDirection;
	
	UFUNCTION()
	void PlayAnimationByActorDirection(AActor* Actor);
	
	UFUNCTION()
	void StopAnimationByActorDirection(AActor* Actor);
#pragma endregion
};
