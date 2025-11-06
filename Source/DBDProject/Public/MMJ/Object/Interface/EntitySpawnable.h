// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EntitySpawnable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEntitySpawnable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 엔티티가 스폰되는 오브젝트들을 위한 인터페이스
 */
class DBDPROJECT_API IEntitySpawnable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual void SpawnEntity() = 0;
};
