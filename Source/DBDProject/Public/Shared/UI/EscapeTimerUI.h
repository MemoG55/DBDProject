// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EscapeTimerUI.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UEscapeTimerUI : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY()
	float MaxEscapeTime;
	
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetDisplay();
	
	UFUNCTION()
	void Update(float NewValue);

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar;
};
