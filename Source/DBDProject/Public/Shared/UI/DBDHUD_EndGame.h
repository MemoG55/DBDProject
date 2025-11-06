// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DBDHUD_EndGame.generated.h"

struct FGameplayTag;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDBDHUD_EndGame : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	FString TextblockText;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* IsEscaped;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> ExitButton;

	UFUNCTION()
	void BindingPlayerController();
	
};

