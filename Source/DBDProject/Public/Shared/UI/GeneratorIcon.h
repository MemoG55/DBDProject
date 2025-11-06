// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/UI/BaseIcon.h"
#include "GeneratorIcon.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGeneratorIcon : public UBaseIcon
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,meta=(BindWidget));
	TObjectPtr<UImage> ExitDoorIcon;

	UPROPERTY(BlueprintReadWrite,meta=(BindWidget));
	TObjectPtr<UTextBlock> LeftDoorText;

	UFUNCTION()
	void SetGeneratorImage(int32 LeftGenerator);
	
protected:
	virtual void NativeConstruct() override;
};
