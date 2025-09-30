// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/Item/SurvivorItem.h"
#include "ChineseFireCracker.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API AChineseFireCracker : public ASurvivorItem
{
	GENERATED_BODY()

public:
	AChineseFireCracker();
public:
	
	virtual void OnEquipItem() override;
	virtual void OnInitialized_Implementation() override;
	virtual void OnItemUsed() override;
	UPROPERTY(EditDefaultsOnly, Category = "FireCracker")
	float ExplodeDelay = 2.f;
	UPROPERTY(EditDefaultsOnly, Category = "FireCracker")
	float ExplodeRadius = 200.f;
protected:
	UFUNCTION()
	void Explode();
	FTimerHandle ExplodeTimerHandle;
};
