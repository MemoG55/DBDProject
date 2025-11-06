// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/GAS/GA/ObjGameplayAbility.h"
#include "GA_Destroy.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Destroy : public UObjGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_Destroy();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
#pragma region DestroyTask:
	// 어빌리티 시작할 때 재생될 몽타주
	UPROPERTY(EditAnywhere, Category = "DestroyTask")
	UAnimMontage* DestroyMontage;
	// 어빌리티 종료될 때 재생될 몽타주
	UPROPERTY(EditAnywhere, Category = "DestroyTask")
	UAnimMontage* DestroyEndMontage;
	
	virtual void ExecuteGameplayEffectAndCue(FGameplayEventData Data) override;
#pragma endregion
};
