// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/Component/InteractableComponent.h"
#include "SurvivorInteractableComponent.generated.h"

class ASurvivorCharacter;
class USurvivorAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API USurvivorInteractableComponent : public UInteractableComponent
{
	GENERATED_BODY()
public:
	USurvivorInteractableComponent();
	virtual void StartInteraction(AActor* Actor) override;
	virtual bool CanInteraction(AActor* Actor) override;
	virtual void TickInteraction(AActor* Actor) override;
	virtual void FinishInteraction(AActor* Actor) override;
protected:
	virtual void BeginPlay() override;
	void PlayTick();
	TObjectPtr<ASurvivorCharacter> OwningSurvivor;
	TObjectPtr<USurvivorAbilitySystemComponent> OwningSurvivorASC;
	float GetHealSpeedAttributeValue();
	virtual void OnCompleted_Implementation() override;

	FTimerHandle TickTimerHandle;
};
