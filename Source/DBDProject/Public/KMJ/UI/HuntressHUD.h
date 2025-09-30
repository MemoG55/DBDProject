// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KMJ/UI/KillerHUD.h"
#include "HuntressHUD.generated.h"

class UTextBlock;
class AKillerHuntress;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UHuntressHUD : public UKillerHUD
{
	GENERATED_BODY()
	
public:
	UHuntressHUD();

	UFUNCTION(BlueprintCallable)
	void OnAxeNumberChanged(float NewAxeNumber);

	UFUNCTION(BlueprintCallable)
	void OnWalkingSpeedChanged(float NewWalkingSpeed);
	
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> CurrentAxeNum;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> WalkingSpeed;

protected:
	AKillerHuntress* Huntress = nullptr;
};
