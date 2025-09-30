// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "TempUIReactToTag.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UTempUIReactToTag : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DescriptionText;

	UPROPERTY(EditAnywhere, Category="Tag")
	FGameplayTag TargetTag;

	UPROPERTY(EditAnywhere, Category="Tag")
	FText Description;
	
	void TagChanged(const FGameplayTag Tag, int32 NewCount);

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
	
	
};
