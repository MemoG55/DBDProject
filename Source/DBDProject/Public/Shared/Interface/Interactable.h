// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"


enum class EPlayerRole:uint8;
class UInteractableComponent;
class UInputMappingContext;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interactable Object(상호작용 오브젝트용 인터페이스)
 */
class DBDPROJECT_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual UInteractableComponent* GetInteractableComponent() const = 0;

};
