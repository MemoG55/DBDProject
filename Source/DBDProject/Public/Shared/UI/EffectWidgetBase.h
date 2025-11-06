// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "EffectWidgetBase.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UEffectWidgetBase : public UUserWidget
{
	GENERATED_BODY()
private:

	UPROPERTY(EditAnywhere, Category="Tag")
	FGameplayTag TargetTag;

	
	void TagChanged(const FGameplayTag Tag, int32 NewCount);

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
	
	
};
