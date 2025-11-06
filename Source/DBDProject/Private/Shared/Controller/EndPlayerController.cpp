// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Controller/EndPlayerController.h"

#include "GameFramework/Character.h"
#include "Shared/GameFramework/End/EndGameMode.h"
#include "Shared/UI/DBDHUD_EndGame.h"

AEndPlayerController::AEndPlayerController()
{
}

void AEndPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController()) return;

	if (!IsValid(EndHUDClass)) return;

	EndHUD = CreateWidget<UDBDHUD_EndGame>(this, EndHUDClass);
	EndHUD->AddToViewport();

	if (EndHUD)
	{
		EndHUD->BindingPlayerController();
	}
	
	FInputModeGameAndUI InputModeGameAndUI;
	SetInputMode(InputModeGameAndUI);

	bShowMouseCursor = true;
}

void AEndPlayerController::GetSeamlessTravelActorList(bool bToEntry, TArray<class AActor*>& ActorList)
{
	Super::GetSeamlessTravelActorList(bToEntry, ActorList);
}

void AEndPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (GetCharacter())
	{
		GetCharacter()->DisableInput(this);
	}
}

void AEndPlayerController::RequestExit_Implementation()
{
	if (AEndGameMode* GM = GetWorld()->GetAuthGameMode<AEndGameMode>())
	{
		GM->HandleExit(this);
	}
}
