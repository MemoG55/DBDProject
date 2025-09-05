// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/GAS/DBDAbilitySystemComponent.h"
#include "ObjAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UObjAbilitySystemComponent : public UDBDAbilitySystemComponent
{
	GENERATED_BODY()
public:
	UObjAbilitySystemComponent();
	
	UFUNCTION(BlueprintCallable)
	class ADBDObject* GetOwnerActorFromActorInfo();

	void TaskUpdated(const FOnAttributeChangeData& OnAttributeChangeData);


private:
	UPROPERTY(EditDefaultsOnly, Category = "GA")
	class UObjDataAsset* ObjDataAsset;

	void AuthApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect, int32 Level);

public:
	void ApplyInitializeEffects();

	void OperatingInitializedAbilities();

	void ServerSideInit();
	void InitializeBaseAttributes();

	UFUNCTION(BlueprintCallable)
	const UObjDataAsset* GetObjDataAsset() const;

	UFUNCTION(BlueprintCallable)
	bool IsMaxTask() const;

	
};
