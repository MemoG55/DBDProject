// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/GameFramework/DBDPlayerState.h"

#include "Engine/AssetManager.h"
#include "JMS/GAS/SurvivorAttributeSet.h"
#include "KMJ/AbilitySystem/HuntressAttributeSet.h"
#include "KMJ/AbilitySystem/KillerAbilitySystemComponent.h"
#include "KMJ/AbilitySystem/KillerAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "Shared/DBDEnum.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/Controller/DBDPlayerController.h"
//#include "Shared/DataAsset/DBDDataBase.h"
#include "JMS/GAS/SurvivorAbilitySystemComponent.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/DataAsset/DBDDataBase.h"
#include "Shared/GAS/DBDAbilitySystemComponent.h"

ADBDPlayerState::ADBDPlayerState()
{
	NetUpdateFrequency = 100.0f;
	PlayerRole = EPlayerRole::Survivor;
}

EPlayerRole ADBDPlayerState::GetPlayerRole() const
{
	return PlayerRole;
}

EPlayerRole ADBDPlayerState::SetPlayerRole(EPlayerRole NewRole)
{
	PlayerRole = NewRole;
	return PlayerRole;
}

EPlayerEndState ADBDPlayerState::GetPlayerEndState() const
{
	return PlayerEndState;
}

void ADBDPlayerState::SetPlayerEndState(EPlayerEndState EndState)
{
	PlayerEndState = EndState;
}

//
void ADBDPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);
	
	if (ADBDPlayerState* NewPS = Cast<ADBDPlayerState>(PlayerState))
	{
		NewPS->SurvivorLoadout = SurvivorLoadout;
		NewPS->KillerLoadout = KillerLoadout;
		NewPS->SetPlayerRole(PlayerRole);
		NewPS->SetPlayerEndState(PlayerEndState);
	}
}

void ADBDPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void ADBDPlayerState::OnRep_SurvivorLoadout(FSurvivorLoadout OldLoadout)
{
	OnPlayerStateUpdatedToSelf.Broadcast();
	OnPlayerStateUpdatedToOther.Broadcast(this);
}

void ADBDPlayerState::OnRep_KillerLoadout(FKillerLoadout OldLoadout)
{
	OnPlayerStateUpdatedToSelf.Broadcast();
	OnPlayerStateUpdatedToOther.Broadcast(this);
}

void ADBDPlayerState::OnRep_PlayerRole()
{
	OnPlayerRoleUpdatedToSelf.Broadcast();
	OnPlayerRoleUpdatedToOther.Broadcast(this);
}

void ADBDPlayerState::OnRep_OnPlayerStateAddedToSelf(ADBDPlayerState* NewPS)
{
	OnPlayerStateAddedToSelf.Broadcast(NewPS);	
}


void ADBDPlayerState::OnRep_OnPlayerStateUpdatedFromOther(ADBDPlayerState* OtherPS)
{
	// Receive The Other PlayerState Updated
	OnPlayerStateUpdatedFromOther.Broadcast(OtherPS);
}
void ADBDPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(ADBDPlayerState, SurvivorLoadout, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ADBDPlayerState, KillerLoadout, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ADBDPlayerState, PlayerRole, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ADBDPlayerState, PlayerEndState, COND_None, REPNOTIFY_Always);
}
