// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Component/ItemInteractableComponent.h"

#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/Item/SurvivorItem.h"
#include "Shared/Interface/Interactor.h"

bool UItemInteractableComponent::CanInteraction(AActor* Actor)
{
	IInteractor* Interactor = Cast<IInteractor>(Actor);
	return Interactor->GetInteractorRole() == EPlayerRole::Survivor;
}

void UItemInteractableComponent::StartInteraction(AActor* Actor)
{
	Super::StartInteraction(Actor);
	ASurvivorCharacter* InteractingSurvivor = Cast<ASurvivorCharacter>(Actor);
	ASurvivorItem* OwnerAsSurvivorItem = GetOwnerAsSurvivorItem();
	if (InteractingSurvivor && OwnerAsSurvivorItem)
	{
		InteractingSurvivor->EquipItem(OwnerAsSurvivorItem);
	}
}

void UItemInteractableComponent::SetInteractable(bool bInteractable)
{
	if (bInteractable)
	{
		SetCollisionProfileName("InteractionOnly");
	}
	else
	{
		SetCollisionProfileName("NoCollision");
	}
}

ASurvivorItem* UItemInteractableComponent::GetOwnerAsSurvivorItem()
{
	return Cast<ASurvivorItem>(GetOwner());
}
