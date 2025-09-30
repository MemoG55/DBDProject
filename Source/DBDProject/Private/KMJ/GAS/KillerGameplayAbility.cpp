// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/GAS/KillerGameplayAbility.h"

#include "KMJ/AbilitySystem/KillerAbilitySystemComponent.h"
#include "KMJ/Character/KillerCharacter.h"
#include "Shared/Component/InteractorComponent.h"


UInteractorComponent* UKillerGameplayAbility::GetInteractorComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UInteractorComponent>();
}

UKillerAbilitySystemComponent* UKillerGameplayAbility::GetKillerAbilitySystemComponentFromActorInfo() const
{
	return Cast<UKillerAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

UAnimInstance* UKillerGameplayAbility::GetAnimInstance() const
{
	USkeletalMeshComponent* OwningSkeletalMeshComponent = GetOwningComponentFromActorInfo();
	if (OwningSkeletalMeshComponent)
	{
		return OwningSkeletalMeshComponent->GetAnimInstance();
	}
	return nullptr;
}

AKillerCharacter* UKillerGameplayAbility::GetKillerCharacterFromActorInfo() const
{
	return Cast<AKillerCharacter>(GetAvatarActorFromActorInfo());
}
