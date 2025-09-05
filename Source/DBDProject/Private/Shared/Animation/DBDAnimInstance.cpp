// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Animation/DBDAnimInstance.h"
#include "AbilitySystemGlobals.h"
#include "Misc/DataValidation.h"
#include "Shared/GAS/DBDAbilitySystemComponent.h"

UDBDAnimInstance::UDBDAnimInstance()
{
}

void UDBDAnimInstance::InitializeWithAbilitySystem(UAbilitySystemComponent* ASC)
{
	if (ASC)
	{
		GameplayTagPropertyMap.Initialize(this, ASC);
	}
}


// Possess로직이 먼저 실행되어야 ADBDCharacter의 ASC에 접근이 가능합니다.
void UDBDAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

#if WITH_EDITOR
EDataValidationResult UDBDAnimInstance::IsDataValid(class FDataValidationContext& Context) const
{
	Super::IsDataValid(Context);

	GameplayTagPropertyMap.IsDataValid(this, Context);

	return ((Context.GetNumErrors() > 0) ? EDataValidationResult::Invalid : EDataValidationResult::Valid);
}
#endif // WITH_EDITOR

void UDBDAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UDBDAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
