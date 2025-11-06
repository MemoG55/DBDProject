// Fill out your copyright notice in the Description page of Project Settings.
// TODO: 베이스 어빌리티로 전환
#pragma once

#include "CoreMinimal.h"
#include "JMS/GAS/GA/SurvivorInteractionAbility.h"
#include "JMS/GAS/SurvivorGameplayAbility.h"
#include "Shared/DBDEnum.h"
#include "GA_Survivor_RepairGenerator.generated.h"

class AObj_Generator;
/**
 *  TODO: 어트리뷰트 값 불러와서 스킬체크 빈도수 조절
 *  TODO: OnSkillCheckEnd에서 발전기에 스킬체크 결과 전달
 */
UCLASS()
class DBDPROJECT_API UGA_Survivor_RepairGenerator : public USurvivorInteractionAbility
{
	GENERATED_BODY()

public:
	UGA_Survivor_RepairGenerator();
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void Server_SendSkillCheckResult_Implementation(ESkillCheckResult Result) override;
	virtual void OnSkillCheckBad() override;
	UFUNCTION()
	void OnFailedMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	FName CurrentDirection;
};
