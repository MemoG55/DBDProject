// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/GA/ObjGameplayAbility.h"

UDBDAbilitySystemComponent* UObjGameplayAbility::GetMGAbilitySystemComponentFromActorInfo() const
{
	return Cast<UDBDAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

UAnimInstance* UObjGameplayAbility::GetAnimInstance() const
{
	if (USkeletalMeshComponent* OwningSkeletalMeshComponent = GetOwningComponentFromActorInfo())
	{
		return OwningSkeletalMeshComponent->GetAnimInstance();
	}

	return nullptr;
}