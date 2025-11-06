// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/Component/IC_Hook.h"
#include "MMJ/Object/GAS/GA/Object/Active/GA_Active.h"
#include "GA_EntityHook.generated.h"

enum class EHookPhase : uint8;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_EntityHook : public UGA_Active
{
	GENERATED_BODY()

public:
	UGA_EntityHook();
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UFUNCTION()
	void OnCompleteAbility();
private:
	UPROPERTY(EditAnywhere)
	FFloatCurve DissolveFloatCurve;


	FDelegateHandle CapturedActorHPDelegateHandle;

	UPROPERTY()
	float DissolvePercent = 0.f;
	UPROPERTY()
	float CachedDissolvePercent = 0.f;

	UPROPERTY()
	float HookHP;
	UPROPERTY()
	float MaxHookHP;

	UPROPERTY()
	TObjectPtr<class AObj_Hook> Hook;
	
	UPROPERTY()
	TObjectPtr<UIC_Hook> HookIC;

	UPROPERTY()
	TWeakObjectPtr<class ADBDCharacter> CachedCapturedActor;
	
	void OnCapturedActorHealthUpdated(const FOnAttributeChangeData& OnAttributeChangeData);

	
	UPROPERTY(EditAnywhere, Category = "EntityAnimation")
	UAnimMontage* EntityMontage_EntityStart;
	UPROPERTY(EditAnywhere, Category = "EntityAnimation")
	UAnimMontage* EntityMontage_Entity;
	UPROPERTY(EditAnywhere, Category = "EntityAnimation")
	UAnimMontage* EntityMontage_Final;

	UPROPERTY(EditAnywhere, Category = "EntityAnimation")
	UAnimMontage* EntityMontage_SkillCheckFail;

#pragma region PhaseFunctions:
	UPROPERTY()
	EHookPhase HookPhase = EHookPhase::Phase_None;
	
	// 페이즈별 실행될 함수모음
	UFUNCTION()
	void OnPhaseNormal();

	UFUNCTION()
	void OnPhaseEntity();

	UFUNCTION()
	void OnPhaseFinal();

	UFUNCTION()
	void OnInteractWithHook(FGameplayTag EventTag);
#pragma endregion

protected:
	virtual void ExecuteTaskByEvent(FGameplayEventData Data) override;

	virtual void ExecuteGameplayEffectAndCue(FGameplayEventData Data) override;
};


