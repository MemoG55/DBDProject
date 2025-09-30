// Fill out your copyright notice in the Description page of Project Settings.
// TODO: 베이스 어빌리티로 전환
#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/GA/SurvivorInteractionAbility.h"
#include "JMS/GAS/SurvivorGameplayAbility.h"
#include "Shared/DBDEnum.h"
#include "GA_SurvivorRepairGenerator.generated.h"

class AObj_Generator;
/**
 *  TODO: 어트리뷰트 값 불러와서 스킬체크 빈도수 조절
 *  TODO: OnSkillCheckEnd에서 발전기에 스킬체크 결과 전달
 */
UCLASS()
class DBDPROJECT_API UGA_SurvivorRepairGenerator : public USurvivorInteractionAbility
{
	GENERATED_BODY()
	
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* RepairMontage;


	UPROPERTY(EditDefaultsOnly, Category = "GE")
	TSubclassOf<UGameplayEffect> RepairGE;

public:
	UGA_SurvivorRepairGenerator();
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
	TObjectPtr<AObj_Generator> CachedGenerator;
	FTimerHandle SkillCheckTimerHandle;
	void SetSkillCheckTimer(float frequency);
	void PlaySkillCheck();
	void OnSkillCheckInterrupted();
};
