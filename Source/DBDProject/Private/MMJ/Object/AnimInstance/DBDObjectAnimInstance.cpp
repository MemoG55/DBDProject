// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/AnimInstance/DBDObjectAnimInstance.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"

UDBDObjectAnimInstance::UDBDObjectAnimInstance()
{
}

void UDBDObjectAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningObject = Cast<ADBDObject>(GetOwningActor());
}

void UDBDObjectAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UDBDObjectAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UDBDObjectAnimInstance::UpdateProgress(float NewValue)
{
	InteractionProgress = NewValue;
}


void UDBDObjectAnimInstance::SetSlotActive(bool Activation)
{
}

bool UDBDObjectAnimInstance::DoesObjHasTag(FGameplayTag Tag) const
{
	if (OwningObject)
	{
		return UDBDBlueprintFunctionLibrary::NativeActorHasTag(OwningObject, Tag);
	}
	return false;
}
