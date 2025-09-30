// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "HookHPProgressBar.generated.h"

struct FOnAttributeChangeData;
class UProgressBar;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UHookHPProgressBar : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar;

	UPROPERTY(EditAnywhere, Category="Attribute")
	FGameplayAttribute CurrentValueAttribute;
	UPROPERTY(EditAnywhere, Category="Attribute")
	FGameplayAttribute MaxValueAttribute;

	UPROPERTY(EditAnywhere, Category="Tag")
	FGameplayTag TargetTag;
	
	void TagChanged(const FGameplayTag Tag, int32 NewCount);


	void SetPercent(float Percent);

	void AttributeChanged(const FOnAttributeChangeData& Data);

	float CachedMaxValue;

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;	
	
	
};
