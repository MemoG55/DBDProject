// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GA/SurvivorInteractionAbility.h"

#include "Shared/DBDGameplayTags.h"
#include "Shared/Interface/Interactor.h"


USurvivorInteractionAbility::USurvivorInteractionAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ActivationBlockedTags.AddTag(DBDGameplayTags::Survivor_Status_Captured);
	ActivationBlockedTags.AddTag(DBDGameplayTags::Survivor_Status_Dying);
	ActivationBlockedTags.AddTag(DBDGameplayTags::Survivor_Status_Dead);
	ActivationBlockedTags.AddTag(DBDGameplayTags::Survivor_Status_Escaped);
	ActivationBlockedTags.AddTag(DBDGameplayTags::Survivor_Status_Hooked);
}

UInteractorComponent* USurvivorInteractionAbility::GetInteractorComponentFromActorInfo() const
{
	IInteractor* Interactor = Cast<IInteractor>(GetAvatarActorFromActorInfo());
	if (Interactor)
	{
		return Interactor->GetInteractorComponent();
	}
	return nullptr;
}
