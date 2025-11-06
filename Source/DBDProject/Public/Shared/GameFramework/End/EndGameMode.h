// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndGameMode.generated.h"

class ADBDPlayerState;
class ASurvivorCharacter;
class ADBDCharacter;
class APlayerStart;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API AEndGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AEndGameMode();

	virtual void GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList) override;

	virtual void PostSeamlessTravel() override;

	virtual void HandleSeamlessTravelPlayer(AController*& C) override;

	virtual void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC) override;

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName = L"") override;

	ASurvivorCharacter* SpawnSurvivorCharacter(ADBDPlayerState* DBDPS, FTransform SpawnTransform);

	void HandleExit(APlayerController* PC);
private:
	UPROPERTY(EditAnywhere, Category = "GameMode",meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADBDCharacter> KillerCharacterClass;

	UPROPERTY()
	TArray<APlayerStart*> SurvivorPlayerStarts;

	UPROPERTY()
	int32 SurvivorSpawnCurrentIndex = 0;
	
};
