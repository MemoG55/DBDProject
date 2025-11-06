// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/GameFramework/Lobby/LobbyPlayerState.h"

#include "Net/UnrealNetwork.h"
#include "Shared/Controller/LobbyPlayerController.h"


void ALobbyPlayerState::SetReady(bool NewValue)
{
	bIsReady = NewValue;
}

bool ALobbyPlayerState::GetReady()
{
	return bIsReady;
}

void ALobbyPlayerState::OnRep_IsReady()
{
	// UI 업데이트
	OnReadyStateUpdatedToSelf.Broadcast();
	//OnPlayerStateUpdatedToOther.Broadcast(this);
}

void ALobbyPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ALobbyPlayerState, bIsReady, COND_None, REPNOTIFY_Always);
}

void ALobbyPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	if (ADBDPlayerState* NewPS = Cast<ADBDPlayerState>(PlayerState))
	{
		NewPS->SurvivorLoadout = SurvivorLoadout;
		NewPS->KillerLoadout = KillerLoadout;
		NewPS->SetPlayerRole(PlayerRole);
	}
}

