// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Controller/DBDPlayerController.h"
#include "CommonActivatableWidget.h"

void ADBDPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (UIBaseClass)
	{
		UIBase = CreateWidget<UCommonActivatableWidget>(this,UIBaseClass);
		UIBase->AddToViewport();
	}
	SetInputMode(FInputModeGameOnly());
}
