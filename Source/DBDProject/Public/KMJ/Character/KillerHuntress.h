// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KMJ/Character/KillerCharacter.h"
#include "KillerHuntress.generated.h"

struct FInputActionValue;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API AKillerHuntress : public AKillerCharacter
{
	GENERATED_BODY()
public:
	AKillerHuntress();
	virtual void InitKillerAttribute();
};
