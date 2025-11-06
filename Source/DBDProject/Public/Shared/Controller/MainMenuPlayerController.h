// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

class UMainMenuHUD;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainMenuHUD> MainMenuHUDClass;
	
	UPROPERTY()
	UMainMenuHUD* MainMenuHUD;
};
