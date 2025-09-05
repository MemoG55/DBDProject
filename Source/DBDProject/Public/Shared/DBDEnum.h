// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EKillerName : uint8
{
	Huntress	UMETA(DisplayName = "Huntress"),
	Nurse		UMETA(DisplayName = "Nurse"),
};

UENUM(BlueprintType)
enum class EKillerAbilityInputID : uint8
{
	None		UMETA(DisplayName = "None"),
	Attack		UMETA(DisplayName = "Attack"),
	Skill		UMETA(DisplayName = "Skill"),
	Interact		UMETA(DisplayName = "Interact"),
	Drop		UMETA(DisplayName = "Drop")
};

class DBDPROJECT_API DBDEnum
{
public:
};
