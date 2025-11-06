// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Controller/MainMenuPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/UI/MainMenuHUD.h"

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalPlayerController())
		return;
	
	if (!MainMenuHUDClass)
	{
		//Debug::Print(TEXT("Can't find MainMenuHUDClass"), -1, FColor::Red);
		return;
	}
	
	MainMenuHUD = CreateWidget<UMainMenuHUD>(this, MainMenuHUDClass);
	MainMenuHUD->AddToViewport();
	
	FInputModeGameAndUI InputModeGameAndUI;
	SetInputMode(InputModeGameAndUI);

	bShowMouseCursor = true;
}
