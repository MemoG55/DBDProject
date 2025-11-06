// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Animation/AnimInstance.h"
#include "DBDAnimInstance.generated.h"

/**
 * 
 */
class ACharacter;
class UCharacterMovementComponent;
UCLASS()
class DBDPROJECT_API UDBDAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UDBDAnimInstance();
	virtual void InitializeWithAbilitySystem(UAbilitySystemComponent* ASC);

	virtual void NativeBeginPlay() override;
protected:

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif // WITH_EDITOR

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:

	// Gameplay tags that can be mapped to blueprint variables. The variables will automatically update as the tags are added or removed.
	// These should be used instead of manually querying for the gameplay tags.
	UPROPERTY(EditDefaultsOnly, Category = "GameplayTags")
	FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly, Category = "Movement")
	TEnumAsByte<EMovementMode> CurrentMovementMode;
private:
	UPROPERTY()
	class ACharacter* CurrentOwnerCharacter;

	UPROPERTY()
	class UCharacterMovementComponent* CurrentOwnerMovementComponent;
	
	float CurrentSpeed;
};
