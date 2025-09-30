// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/SurvivorGameplayAbility.h"

#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/Component/SkillCheckComponent.h"
#include "JMS/GAS/SurvivorAbilitySystemComponent.h"
#include "Shared/Component/InteractorComponent.h"


UInteractableComponent* USurvivorGameplayAbility::GetInteractableComponentFromActorInfo() const
{
	IInteractable* Interactable = Cast<IInteractable>(GetAvatarActorFromActorInfo());
	if (Interactable)
	{
		return Interactable->GetInteractableComponent();
	}
	return nullptr;
}

USkillCheckComponent* USurvivorGameplayAbility::GetSkillCheckComponentFromActorInfo() const
{
	if (ASurvivorCharacter* SurvivorCharacter = Cast<ASurvivorCharacter>(GetAvatarActorFromActorInfo()))
	{
		return SurvivorCharacter->GetSkillCheckComponent();
	}
	return nullptr;
}

USurvivorAbilitySystemComponent* USurvivorGameplayAbility::GetSurvivorAbilitySystemComponentFromActorInfo() const
{
	return Cast<USurvivorAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

UAnimInstance* USurvivorGameplayAbility::GetAnimInstance() const
{
	USkeletalMeshComponent* OwningSkeletalMeshComponent = GetOwningComponentFromActorInfo();
	if (OwningSkeletalMeshComponent)
	{
		return OwningSkeletalMeshComponent->GetAnimInstance();
	}
	return nullptr;
}

ASurvivorCharacter* USurvivorGameplayAbility::GetSurvivorCharacterFromActorInfo() const
{
	return Cast<ASurvivorCharacter>(GetAvatarActorFromActorInfo());
}
