// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "DBDWidgetInterface.generated.h"

class UDBDWidgetComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDBDWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DBDPROJECT_API IDBDWidgetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UDBDWidgetComponent* GetWidgetComponent() const = 0;
	
};
