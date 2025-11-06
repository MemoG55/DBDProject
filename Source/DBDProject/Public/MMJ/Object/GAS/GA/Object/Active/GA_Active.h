// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/GAS/GA/ObjGameplayAbility.h"
#include "GA_Active.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Active : public UObjGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;


#pragma region InteractTask:
	UPROPERTY()
	FTimerHandle TaskTimerHandle;

	// 상호작용 함수 실행 주기
	UPROPERTY(EditAnywhere, Category = "InteractTask")
	float TaskInterval;

	// 상호작용 함수 루프 여부
	UPROPERTY(EditAnywhere, Category = "InteractTask")
	bool TaskLoop = true;

	// 상호작용 타이머 설정 + 설정 조건을 추가하기 위해 virtual 선언
	UFUNCTION()
	virtual void SetTaskTimer();

	// 상호작용 타이머 해제 + 해제 조건을 추가하기 위해 virtual 선언
	UFUNCTION()
	virtual void UnSetTaskTimer();

	// 실제 실행되는 상호작용 내용들 + 각 오브젝트마다 내용이 다르므로 virtual 선언
	UFUNCTION()
	virtual void TaskFunction();
#pragma endregion

#pragma region InteractWidget:
	UPROPERTY(EditAnywhere, Category = "InteractWidget")
	bool bUseWidget = false;

	// InteractWithActor에 연결할 델리게이트함수
	UFUNCTION()
	virtual void SetWidget(AActor* Actor);

	// DisconnectWithActor에 연결할 델리게이트함수
	UFUNCTION()
	virtual void UnSetWidget(AActor* Actor);
#pragma endregion 
};
