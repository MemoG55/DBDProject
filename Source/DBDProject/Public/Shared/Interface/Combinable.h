// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Combinable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombinable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 액터가 추가로 결합되어있는 형태에서 쓸 수 있는? 인터페이스 구현(탈출구의 탈출영역, 오브젝트의 엔티티 같은..) 
 */
class DBDPROJECT_API ICombinable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual void CreateCombinedActor() = 0;

	UFUNCTION()
	virtual AActor* GetCombinedActor() const = 0;
};
