// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityProgressWidget.generated.h"

class UTextBlock;
class UImage;
class UProgressBar;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UAbilityProgressWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnUpdate(bool bIsVisible, FText Description, float Percentage);
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category="AbilityProgressWidget")
	float TargetPercent = 0.f;
	UPROPERTY(VisibleAnywhere, Category="AbilityProgressWidget")
	float DisplayedPercent = 0.f;
	UPROPERTY(EditAnywhere, Category="AbilityProgressWidget")
	float ProgressInterpSpeed = 20.f;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UProgressBar* ProgressBar;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* DescriptionBlock;
	
};
