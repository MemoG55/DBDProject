// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Shared/Animation/DBDAnimInstance.h"
#include "KillerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UKillerAnimInstance : public UDBDAnimInstance
{
	GENERATED_BODY()
protected:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY()
	class AKillerCharacter* KillerOwnerCharacter;

	UPROPERTY()
	class UCharacterMovementComponent* KillerOwnerMovementComponent;

	float KillerSpeed;
	
public:
	UFUNCTION(BlueprintCallable, Category="KillerStateControl", meta=(BlueprintThreadSafe))
	FORCEINLINE float GetSpeed() const{return KillerSpeed;}

	UFUNCTION(BlueprintCallable, Category="KillerStateControl", meta=(BlueprintThreadSafe))
	FORCEINLINE bool IsMoving() const{return KillerSpeed != 0;}

	virtual void InitializeWithAbilitySystem(UAbilitySystemComponent* ASC) override;
	virtual void NativeBeginPlay() override;
};
