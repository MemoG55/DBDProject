// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/GameFramework/Lobby/LobbyGameState.h"

#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Shared/GameFramework/DBDPlayerState.h"

ALobbyGameState::ALobbyGameState()
{
	SurvivorPlayerStates.SetNum(4);
}

void ALobbyGameState::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);
	
	if (ADBDPlayerState* NewPS = Cast<ADBDPlayerState>(PlayerState))
	{
		OnPlayerStateAdded.Broadcast(NewPS);
	}
}

void ALobbyGameState::OnRep_PlayerState()
{
	// UI업데이트
	OnPlayerStatesUpdated.Broadcast();
}

void ALobbyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ALobbyGameState, KillerPlayerState, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ALobbyGameState, SurvivorPlayerStates, COND_None, REPNOTIFY_Always);
}
