// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/AnimInstance/DBDObjectAnimInstance.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "MMJ/Object/ObjFunctionLibrary.h"

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

void UDBDObjectAnimInstance::SetInteracting(bool NewValue)
{
	bIsInteracting = NewValue;
}

void UDBDObjectAnimInstance::SetBroken(bool NewValue)
{
	bIsBroken = NewValue;
}

void UDBDObjectAnimInstance::SetActive(bool NewValue)
{
	bIsActive = NewValue;
}

void UDBDObjectAnimInstance::SetSlotActive(bool Activation)
{
}

bool UDBDObjectAnimInstance::DoesObjHasTag(FGameplayTag Tag) const
{
	if (OwningObject)
	{
		return UObjFunctionLibrary::ActorHasGameplayTag(OwningObject, Tag);
	}
	return false;
}
