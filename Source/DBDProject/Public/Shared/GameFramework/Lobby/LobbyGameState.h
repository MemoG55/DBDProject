// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LobbyGameState.generated.h"

class ADBDPlayerState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLobbyPlayerStatesUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateAdded, ADBDPlayerState*, NewPS);
/**
 * 
 */
UCLASS()
class DBDPROJECT_API ALobbyGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ALobbyGameState();
	// When PlayerStateUpdate(Ex. PlayerRole)
	FOnLobbyPlayerStatesUpdated OnPlayerStatesUpdated;
	// When New PlayerState Enter, and Initialized
	FOnPlayerStateAdded OnPlayerStateAdded;

	virtual void AddPlayerState(APlayerState* PlayerState) override;	
	
	// 단순 UI에 표시할 목적으로 변수로 캐시
	UPROPERTY(ReplicatedUsing = OnRep_PlayerState)
	TObjectPtr<ADBDPlayerState> KillerPlayerState;

	UPROPERTY(ReplicatedUsing = OnRep_PlayerState)
	TArray<TObjectPtr<ADBDPlayerState>> SurvivorPlayerStates;

private:
	UFUNCTION()
	void OnRep_PlayerState();
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	
};
