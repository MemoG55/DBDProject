// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/GAS/DBDAbilitySystemComponent.h"
#include "MMJ/Object/DataAsset/ObjDataAsset.h"
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

	void DamageUpdated(const FOnAttributeChangeData& OnAttributeChangeData);

	virtual void BeginPlay() override;

private:
	UFUNCTION()
	bool CheckAuthority() const;
	
	UPROPERTY(EditDefaultsOnly, Category = "GA")
	class UObjDataAsset* ObjDataAsset;

	UPROPERTY(EditDefaultsOnly, Category = "GA")
	bool bCanDestroy = false;

	void AuthApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect, int32 Level);

public:
	void ApplyInitializeEffects();

	void OperatingInitializedAbilities();

	void ServerSideInit();
	void InitializeBaseAttributes();

	void InitializeAnimInstance();

	UFUNCTION(BlueprintCallable)
	const UObjDataAsset* GetObjDataAsset() const;

	UFUNCTION(BlueprintCallable)
	bool IsMaxTask() const;

	// Attribute를 인자로 받아서 최대치인지 확인
	UFUNCTION(BlueprintCallable)
	bool IsMaxAttribute(const FGameplayAttribute& MaxAttribute, const FGameplayAttribute& CurrentAttribute);

	
	
};
