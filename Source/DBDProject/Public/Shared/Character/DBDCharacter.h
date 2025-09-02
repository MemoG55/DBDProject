// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "DBDCharacter.generated.h"

UCLASS()
class DBDPROJECT_API ADBDCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()


private:

	// IAbilitySystemInterface
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
