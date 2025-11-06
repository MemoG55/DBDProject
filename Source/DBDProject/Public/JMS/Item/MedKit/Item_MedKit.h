// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/Item/SurvivorItem.h"
#include "Item_MedKit.generated.h"

class UMedkitAttributeSet;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API AItem_MedKit : public ASurvivorItem
{
	GENERATED_BODY()
public:
	AItem_MedKit();
	virtual void OnEquipItem() override;
	virtual void OnInitialized_Implementation() override;
	virtual void OnStartUsingItem() override;
	virtual void OnEndUsingItem() override;
	FORCEINLINE float GetNerfSelfHealSpeedMultiplier() const
	{
		return NerfSelfHealSpeedMultiplier;
	}
	FORCEINLINE float GetBuffHealSpeedMultiplier() const
	{
		return BuffHealSpeedMultiplier;
	}
	FORCEINLINE void AddNerfSelfHealSpeedMultiplier(float Amount)
	{
		NerfSelfHealSpeedMultiplier += Amount;
	}
	FORCEINLINE void AddBuffHealSpeedMultiplier(float Amount)
	{
		BuffHealSpeedMultiplier += Amount;
	}
protected:
	virtual void BeginPlay() override;
	float NerfSelfHealSpeedMultiplier = 0.67f;
	float BuffHealSpeedMultiplier = 1.4f;
private:
	UPROPERTY()
	UMedkitAttributeSet* MedkitAttributeSet;
	
	
	
};
