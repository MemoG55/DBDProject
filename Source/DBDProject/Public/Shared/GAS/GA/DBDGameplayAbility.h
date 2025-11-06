// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DBDGameplayAbility.generated.h"

class ADBDCharacter;
class UDBDWidgetComponent;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDBDGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	UDBDWidgetComponent* GetDBDWidgetComponentFromActorInfo() const;
	ADBDCharacter* GetDBDCharacterFromActorInfo() const;

};
