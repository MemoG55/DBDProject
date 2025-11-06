// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/Item/ItemGameplayAbility_Charge.h"
#include "GA_MedKit_HealSelf.generated.h"

enum class ESkillCheckResult : uint8;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_MedKit_HealSelf : public UItemGameplayAbility_Charge
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "GE")
	TSubclassOf<UGameplayEffect> NerfHealSpeedEffect;

public:
	UGA_MedKit_HealSelf();
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
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	float HealInterval = 0.1f;

	UPROPERTY()
	FActiveGameplayEffectHandle NerfEffectHandle;
};
