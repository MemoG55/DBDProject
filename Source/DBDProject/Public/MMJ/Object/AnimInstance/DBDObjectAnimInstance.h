// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimInstance.h"
#include "MMJ/Object/DBDObject.h"
#include "DBDObjectAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDBDObjectAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION()
	void UpdateProgress(float NewValue);

	UFUNCTION()
	void SetInteracting(bool NewValue);

	UFUNCTION()
	void SetBroken(bool NewValue);

	UFUNCTION()
	void SetActive(bool NewValue);

	UFUNCTION(BlueprintCallable)
	void SetSlotActive(bool Activation);
private:
	
protected:
	UPROPERTY()
	ADBDObject* OwningObject;

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool DoesObjHasTag(FGameplayTag Tag) const;
	
	// 현재 진행도
	UPROPERTY(BlueprintReadOnly, Category = "Interaction")
	float InteractionProgress;

	UPROPERTY(BlueprintReadOnly, Category = "Interaction")
	bool bIsInteracting;

	UPROPERTY(BlueprintReadOnly, Category = "Interaction")
	int32 InteractorsCount;

	UPROPERTY(BlueprintReadOnly, Category = "Interaction")
	bool bIsBroken;

	UPROPERTY(BlueprintReadOnly, Category = "Interaction")
	bool bIsActive;

	UPROPERTY(EditDefaultsOnly, Category = "Slot")
	TMap<FName, UAnimSequence*> AnimBySlot;
};
