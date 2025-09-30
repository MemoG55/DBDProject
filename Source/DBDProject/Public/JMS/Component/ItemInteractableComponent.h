// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/Component/InteractableComponent.h"
#include "ItemInteractableComponent.generated.h"

class ASurvivorItem;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UItemInteractableComponent : public UInteractableComponent
{
	GENERATED_BODY()
public:
	virtual bool CanInteraction(AActor* Actor) override;
	virtual void StartInteraction(AActor* Actor) override;
	void SetInteractable(bool bInteractable);

protected:
	ASurvivorItem* GetOwnerAsSurvivorItem();
};
