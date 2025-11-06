// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityNameOnlyWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UAbilityNameOnlyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void OnSetVisibilityAndText(bool bIsVisible, FText Description);
protected:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* DescriptionBlock;
	virtual void NativeConstruct() override;
};
