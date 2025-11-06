// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/UI/BaseIcon.h"
#include "BasePerkIcon.generated.h"

struct FPerkData;
class UTextBlock;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UBasePerkIcon : public UBaseIcon
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> LevelImage1;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> LevelImage2;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> LevelImage3;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> StackText;
	
	UFUNCTION()
	void SetStackText(int InputStack);
	//1: Yellow, 2: Green, 3(Default): Purple
	UFUNCTION()
	void SetIconLevel(ETier Tier);
	
	virtual void SetIconVisible(ESlateVisibility IsVisible);

protected:
	virtual void NativeConstruct() override;
	void InitializePerkIcon(const FPerkData& PerkData);
public:
	UPROPERTY(EditAnywhere, Category = "BasePerkIcon")
	int PerkIndex = 0;
};