// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyLoadOutSlotDesc.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API ULobbyLoadOutSlotDesc : public UUserWidget
{
	GENERATED_BODY()


public:
	UFUNCTION()
	void SetData(const FText& PDisplayName = FText(), const FText& PDescription = FText());
	
	UFUNCTION()
	UTextBlock* GetDescription();

	UFUNCTION()
	UTextBlock* GetDisplayName();
	
private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> Description;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> DisplayName;
	
	
	
};
