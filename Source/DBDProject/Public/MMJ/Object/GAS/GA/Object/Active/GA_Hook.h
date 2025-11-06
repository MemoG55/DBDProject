// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GA_Active.h"
#include "GA_Hook.generated.h"

class ASurvivorCharacter;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Hook : public UGA_Active
{
	GENERATED_BODY()
public:
	UGA_Hook();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
	UPROPERTY()
	TWeakObjectPtr<class ADBDCharacter> CachedCapturedActor;
	
	// 갈고리에 걸리는 순간
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* Montage_Start;

	// 갈고리에서 자력탈출할 때
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* Montage_Escape;

	// 구출될 때
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* Montage_Rescue;

	// 엔티티가 위협을 시작할 때
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* Montage_EntityStart;
	
	// 갈고리에서 희생되었을 때
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* Montage_Finish;

	// 자력탈출 몽타주 재생
	UFUNCTION()
	void Escaped(FGameplayEventData Data);
};
