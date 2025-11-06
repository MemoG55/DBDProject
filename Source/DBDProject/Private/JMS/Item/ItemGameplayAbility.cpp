// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Item/ItemGameplayAbility.h"

#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/GAS/ItemAbilitySystemComponent.h"
#include "JMS/GAS/SurvivorAbilitySystemComponent.h"
#include "JMS/Item/SurvivorItem.h"


UInteractableComponent* UItemGameplayAbility::GetOwnerInteractableComponentFromActorInfo() const
{
	IInteractable* Interactable = Cast<IInteractable>(GetOwnerSurvivorCharacterFromActorInfo());
	if (Interactable)
	{
		return Interactable->GetInteractableComponent();
	}
	return nullptr;
}

UInteractorComponent* UItemGameplayAbility::GetOwnerInteractorComponentFromActorInfo() const
{
	IInteractor* Interactor = Cast<IInteractor>(GetOwnerSurvivorCharacterFromActorInfo());
	if (Interactor)
	{
		return Interactor->GetInteractorComponent();
	}
	return nullptr;
}

USkillCheckComponent* UItemGameplayAbility::GetOwnerSkillCheckComponentFromActorInfo() const
{
	if (ASurvivorCharacter* SurvivorCharacter = GetOwnerSurvivorCharacterFromActorInfo())
	{
		return SurvivorCharacter->GetSkillCheckComponent();
	}
	return nullptr;
}

USurvivorAbilitySystemComponent* UItemGameplayAbility::GetOwnerSurvivorAbilitySystemComponentFromActorInfo() const
{
	if (ASurvivorCharacter* SurvivorCharacter = GetOwnerSurvivorCharacterFromActorInfo())
	{
		return Cast<USurvivorAbilitySystemComponent>(SurvivorCharacter->GetAbilitySystemComponent());
	}
	return nullptr;
}

UAnimInstance* UItemGameplayAbility::GetOwnerAnimInstance() const
{
	if (ASurvivorCharacter* SurvivorCharacter = GetOwnerSurvivorCharacterFromActorInfo())
	{
		USkeletalMeshComponent* OwnerMesh = SurvivorCharacter->GetMesh();
		if (OwnerMesh)
		{
			return OwnerMesh->GetAnimInstance();
		}
	}
	return nullptr;
}

ASurvivorCharacter* UItemGameplayAbility::GetOwnerSurvivorCharacterFromActorInfo() const
{
	return Cast<ASurvivorCharacter>(GetAvatarActorFromActorInfo()->GetOwner());
}

UItemAbilitySystemComponent* UItemGameplayAbility::GetItemAbilitySystemComponentFromActorInfo() const
{
	return Cast<UItemAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}
