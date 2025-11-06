// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/DBDEnum.h"
#include "UObject/Interface.h"

#include "Interactor.generated.h"

class IInteractable;
class UInteractorComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UInteractor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DBDPROJECT_API IInteractor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UInteractorComponent* GetInteractorComponent() const = 0;
	// 컴포넌트 오너가 생존자인지 살인마인지 확인해야 알맞은 IMC를 받을 수 있음
	virtual EPlayerRole GetInteractorRole() const = 0;
	
};
