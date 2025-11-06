// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/GAS/GA/DBDGameplayAbility.h"
#include "ObjGameplayAbility.generated.h"

class UObjAbilitySystemComponent;
class UInteractableComponent;
class ADBDObject;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UObjGameplayAbility : public UDBDGameplayAbility
{
	GENERATED_BODY()
public:
	UObjGameplayAbility();
	
#pragma region GetOwnerInfo:
	UFUNCTION(BlueprintPure, Category = "GA")
	UObjAbilitySystemComponent* GetObjAbilitySystemComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "GA")
	UAnimInstance* GetAnimInstance() const;

	UFUNCTION(BlueprintPure, Category = "GA")
	ADBDObject* GetOwnerObjectFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "GA")
	UInteractableComponent* GetInteractableComponentFromActorInfo() const;
#pragma endregion
	

#pragma region OwnerInfo:
protected:
	UPROPERTY()
	ADBDObject* OwningObject;

	UPROPERTY()
	UObjAbilitySystemComponent* OwningObjectASC;

	UPROPERTY()
	class UICObject* ObjInteractableComponent;

	UPROPERTY()
	TArray<AActor*> CachedInteractors;

	UPROPERTY()
	AActor* CachedInteractor;
#pragma endregion
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void CheckAuthority();

protected:
	// 어빌리티가 실행되면 자동으로 로직이 실행되는지?
	UPROPERTY(EditAnywhere)
	bool bAutoActive;

	// WaitGameplayEvent 로 전달받을 태그
	UPROPERTY(EditAnywhere)
	FGameplayTag ActiveTag;
	
	UPROPERTY()
	class UAbilityTask_WaitGameplayEvent* WaitTask;

	// 몽타주와 같은 상호작용 시점이 애니메이션 모션에 따라 달라지는 경우를 위해 virtual 선언
	UFUNCTION()
	virtual void ExecuteTaskByEvent(FGameplayEventData Data) {};
	
	// GameplayCue 태그
	UPROPERTY(EditAnywhere)
	FGameplayTag GameplayCueTag;

	// GameplayEffect와 Cue를 재생하기위한 함수 선언
	UFUNCTION()
	virtual void ExecuteGameplayEffectAndCue(FGameplayEventData Data);

	// 상호작용이 일어날 때 재생될 몽타주
	UPROPERTY(EditAnywhere, Category = "InteractTask")
	UAnimMontage* TaskMontage;

	// 몽타주 재생을 오브젝트의 Multicast함수로 실행 (기본 TaskMontage 재생)
	UFUNCTION()
	void ObjectPlayMontage(UAnimMontage* Montage = nullptr);

	// 몽타주 정지를 오브젝트의 Multicast함수로 실행 (기본 TaskMontage 정지)
	UFUNCTION()
	void ObjectStopMontage(UAnimMontage* Montage = nullptr);

};
