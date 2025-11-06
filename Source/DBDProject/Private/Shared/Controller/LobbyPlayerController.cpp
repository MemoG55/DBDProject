// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Controller/LobbyPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/GameFramework/Lobby/LobbyGameMode.h"
#include "Shared/GameFramework/Lobby/LobbyPlayerState.h"
#include "Shared/UI/Lobby/LobbyHUD.h"
#include "Shared/UI/Lobby/LobbyLoadOutSlot.h"
#include "Shared/UI/Lobby/LobbyLoadOutWindow.h"


ALobbyPlayerController::ALobbyPlayerController()
{
	bNetLoadOnClient = true;
}

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController()) return;

	if (!IsValid(LobbyHUDClass)) return;
	
	LobbyHUD = CreateWidget<ULobbyHUD>(this, LobbyHUDClass);
	LobbyHUD->AddToViewport();

	if (LobbyHUD)
	{
		LobbyHUD->BindingPlayerController();
	}
	
	FInputModeGameAndUI InputModeGameAndUI;
	SetInputMode(InputModeGameAndUI);

	bShowMouseCursor = true;
}

void ALobbyPlayerController::GetSeamlessTravelActorList(bool bToEntry, TArray<class AActor*>& ActorList)
{
	Super::GetSeamlessTravelActorList(bToEntry, ActorList);
	
}

void ALobbyPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (ADBDPlayerState* PS = GetPlayerState<ADBDPlayerState>())
	{
		if (LobbyHUD)
		{
			LobbyHUD->BindingPlayerState(PS);
			if (LobbyHUD->GetLoadOutWindow())
			{
				LobbyHUD->GetLoadOutWindow()->BindingPlayerState(PS);
			}
		}
	}
}

void ALobbyPlayerController::SetCharacterMesh_Implementation(const FString& SelectString,
	ESelectInfo::Type SelectionType)
{
	if (ALobbyGameMode* GM = GetWorld()->GetAuthGameMode<ALobbyGameMode>()){
		GM->HandleCharacterMesh(GetPlayerState<ALobbyPlayerState>(), FName(SelectString));
	}
}


void ALobbyPlayerController::SetLoadOutPerk_Implementation(const FName& DataRowName, const FPerkData& SourceData)
{
	if (ALobbyGameMode* GM = GetWorld()->GetAuthGameMode<ALobbyGameMode>()){
		GM->HandleLoadOutPerk(GetPlayerState<ALobbyPlayerState>(), DataRowName);
	}
}

void ALobbyPlayerController::SetLoadOutItem_Implementation(const FName& DataRowName, const FItemData& SourceData)
{
	if (ALobbyGameMode* GM = GetWorld()->GetAuthGameMode<ALobbyGameMode>()){
		
		GM->HandleLoadOutItem(GetPlayerState<ALobbyPlayerState>(), DataRowName);
	}
}

void ALobbyPlayerController::SetLoadOutAddOn_Implementation(const FName& DataRowName, const FItemAddonData& SourceData)
{
	if (ALobbyGameMode* GM = GetWorld()->GetAuthGameMode<ALobbyGameMode>()){
		GM->HandleLoadOutAddOn(GetPlayerState<ALobbyPlayerState>(), DataRowName);
	}
}

void ALobbyPlayerController::SetLoadOut_Implementation(ELobbyLoadOutSlotType SlotType)
{
}

void ALobbyPlayerController::SetRole_Implementation()
{
	if (ALobbyPlayerState* PS = GetPlayerState<ALobbyPlayerState>())
	{
		if (ALobbyGameMode* GM = GetWorld()->GetAuthGameMode<ALobbyGameMode>())
		{
			if (PS->GetPlayerRole() == EPlayerRole::Killer)
			{
				GM->HandlePlayerRole(PS, EPlayerRole::Survivor);				
			}
			else
			{
				GM->HandlePlayerRole(PS, EPlayerRole::Killer);
			}
		}
	}
}

void ALobbyPlayerController::SetReady_Implementation()
{
	if (ALobbyPlayerState* PS = GetPlayerState<ALobbyPlayerState>())
	{
		if (ALobbyGameMode* GM = GetWorld()->GetAuthGameMode<ALobbyGameMode>())
		{
			GM->HandlePlayerReadyState(PS, !PS->GetReady());
		}
	}
}
