// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/Item/ItemGameplayAbility_Charge.h"
#include "GA_Toolbox_Repair.generated.h"

enum class ESkillCheckResult : uint8;
class AObj_Generator;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Toolbox_Repair : public UItemGameplayAbility_Charge
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "GE")
	TSubclassOf<UGameplayEffect> BuffRepairSpeedEffect;

public:
	UGA_Toolbox_Repair();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;


	virtual void Server_SendSkillCheckResult_Implementation(ESkillCheckResult Result) override;

	virtual void OnSkillCheckBad() override;
	UFUNCTION()
	virtual void OnFailedMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	FName CurrentDirection;
};
