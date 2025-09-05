// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/GA/ObjGameplayAbility.h"

#include "MMJ/Object/DBDObject.h"

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

ADBDObject* UObjGameplayAbility::GetOwnerObjectFromActorInfo()
{
	if (ADBDObject* Owner = Cast<ADBDObject>(GetOwningActorFromActorInfo()))
	{
		return Owner;
	}
	return nullptr;
}
