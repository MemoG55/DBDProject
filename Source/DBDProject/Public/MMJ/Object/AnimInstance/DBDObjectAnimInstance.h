// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MMJ/Object/Interactable/DBDObject.h"
#include "Shared/Animation/DBDAnimInstance.h"
#include "DBDObjectAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDBDObjectAnimInstance : public UDBDAnimInstance
{
	GENERATED_BODY()

public:
	UDBDObjectAnimInstance();
	virtual void NativeInitializeAnimation() override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeBeginPlay() override;

	UFUNCTION()
	void UpdateProgress(float NewValue);

	UFUNCTION(BlueprintCallable)
	void SetSlotActive(bool Activation);
private:
	
protected:
	UPROPERTY()
	ADBDObject* OwningObject;

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool DoesObjHasTag(FGameplayTag Tag) const;

public:
	// 현재 진행도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	float InteractionProgress;

	// 현재 상호작용중인 사람 수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	int32 InteractorsCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Slot")
	TMap<FName, UAnimSequence*> AnimBySlot;
};
