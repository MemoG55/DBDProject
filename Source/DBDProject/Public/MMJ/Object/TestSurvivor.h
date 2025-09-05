// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "TestSurvivor.generated.h"

class ADBDObject;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API ATestSurvivor : public ASurvivorCharacter
{
	GENERATED_BODY()
public:
	TWeakObjectPtr<ADBDObject> CachedCurrentInteractObject;
	
	UFUNCTION(BlueprintCallable)
	void TryInteract();

	UFUNCTION(BlueprintCallable)
	void CancelInteract();
	
	UFUNCTION(Server, Reliable)
	void Interact_Object(ADBDObject* Object);

	UFUNCTION(BlueprintCallable)
	void SkillCheck();
};
