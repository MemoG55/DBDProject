// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "TempAttributeUI.generated.h"

struct FOnAttributeChangeData;
class UTextBlock;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UTempAttributeUI : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttributeText;

	UPROPERTY(EditAnywhere)
	FText AttributeDescription;

	UPROPERTY(EditAnywhere, Category="Attribute")
	FGameplayAttribute Attribute;
	
	void SetValue(float NewValue);
	FNumberFormattingOptions NumberFormattingOptions;
	
	FString AttributeName;

	void AttributeChanged(const FOnAttributeChangeData& Data);

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
};
