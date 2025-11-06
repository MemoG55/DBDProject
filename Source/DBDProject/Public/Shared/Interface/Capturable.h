// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Capturable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCapturable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 액터를 본인 소유의 변수에 저장하고, 저장한 액터를 반환하는 인터페이스
 * Ex) 갈고리의 HookedSurvivor, 캐비닛의 HidedSurvivor
 */
class DBDPROJECT_API ICapturable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual void Capture(AActor* Actor) = 0;
};
