// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DBDAbilitySystemComponent.generated.h"

class UDA_DBDASCData;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDBDAbilitySystemComponent : public UAbilitySystemComponent
{
public:
	GENERATED_BODY()

private:
	virtual void AuthApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect, int level);
public:
	UDBDAbilitySystemComponent();

	virtual void ServerSideInit();
	virtual void InitializeBaseAttributes()PURE_VIRTUAL(UDBDAbilitySystemComponent::InitializeBaseAttributes,);
		
	UPROPERTY(EditDefaultsOnly, Category = "DataControl")
	UDA_DBDASCData* DBDASCData;

	virtual void OperatingInitializedAbilities();
	virtual void ApplyInitializeEffects();
	virtual void GrantInputAbilities()PURE_VIRTUAL(UDBDAbilitySystemComponent::GrantInputAbilities,);

};
