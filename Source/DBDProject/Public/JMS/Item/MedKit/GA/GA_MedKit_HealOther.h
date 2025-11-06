// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/Item/ItemGameplayAbility_Charge.h"
#include "GA_MedKit_HealOther.generated.h"

class AObj_Generator;
enum class ESkillCheckResult : uint8;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_MedKit_HealOther : public UItemGameplayAbility_Charge
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "GE")
	TSubclassOf<UGameplayEffect> BuffHealSpeedEffect;

	UPROPERTY()
	ASurvivorCharacter* CachedOtherSurvivor;
public:
	UGA_MedKit_HealOther();
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;


	virtual void Server_SendSkillCheckResult_Implementation(ESkillCheckResult Result) override;

	virtual void OnSkillCheckBad() override;

private:
	
	FTimerHandle HealWidgetTimerHandle;
	void UpdateProgressPercentage();

	FActiveGameplayEffectHandle BuffEffectHandle;
	
	
	
};
