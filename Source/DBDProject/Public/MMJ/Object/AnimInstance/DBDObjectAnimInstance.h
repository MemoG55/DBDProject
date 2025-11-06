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

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeBeginPlay() override;
private:
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Owner")
	ADBDObject* OwningObject;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Owner")
	UObjAbilitySystemComponent* OwningObjectASC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Owner")
	class UICObject* OwningObjectIC;

	// 현재 진행도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	float CurrentTask;

	// 총 진행도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	float MaxTask;

public:
	// 진행률
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	float InteractionProgress;

	// 현재 상호작용중인 사람 수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	int32 InteractorsCount;

};
