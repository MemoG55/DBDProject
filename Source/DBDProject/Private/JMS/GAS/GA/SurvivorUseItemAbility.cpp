// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GA/SurvivorUseItemAbility.h"

#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/GAS/ItemAbilitySystemComponent.h"
#include "JMS/Item/SurvivorItem.h"
#include "Shared/DBDGameplayTags.h"


USurvivorUseItemAbility::USurvivorUseItemAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Survivor.Status.Captured")));
	ActivationBlockedTags.AddTag(DBDGameplayTags::Survivor_Status_Dying);
	ActivationBlockedTags.AddTag(DBDGameplayTags::Survivor_Status_Dead);
	ActivationBlockedTags.AddTag(DBDGameplayTags::Survivor_Status_Escaped);
}


UItemAbilitySystemComponent* USurvivorUseItemAbility::GetItemAbilitySystemComponentFromActorInfo() const
{
	if (ASurvivorItem* Item = GetEquippedItemFromActorInfo())
	{
		return Cast<UItemAbilitySystemComponent>(Item->GetAbilitySystemComponent());
	}
	return nullptr; 
}

UInteractorComponent* USurvivorUseItemAbility::GetInteractorComponentFromActorInfo() const
{
	IInteractor* Interactor = Cast<IInteractor>(GetAvatarActorFromActorInfo());
	if (Interactor)
	{
		return Interactor->GetInteractorComponent();
	}
	return nullptr;
}
