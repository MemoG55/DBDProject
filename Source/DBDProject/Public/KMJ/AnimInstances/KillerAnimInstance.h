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
	class AKillerCharacter* OwnerCharacter;

	UPROPERTY()
	class UCharacterMovementComponent* OwnerMovementComponent;

	float Speed;
	
public:
	UFUNCTION(BlueprintCallable, Category="KillerStateControl", meta=(BlueprintThreadSafe))
	FORCEINLINE float GetSpeed() const{return Speed;}

	UFUNCTION(BlueprintCallable, Category="KillerStateControl", meta=(BlueprintThreadSafe))
	FORCEINLINE bool IsMoving() const{return Speed != 0;}

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="KillerStateControl", meta=(BlueprintThreadSafe))
	bool bIsLeftMoving;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="KillerStateControl", meta=(BlueprintThreadSafe))
	bool bIsRightMoving;
};
