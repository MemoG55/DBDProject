// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DBDGameMode.generated.h"


class ADBDCharacter;

/**
 * 
 */
UCLASS()
class DBDPROJECT_API ADBDGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ADBDGameMode();
	
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

public:
	void TEST();
private:
	UPROPERTY(EditAnywhere, Category = "GameMode",meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADBDCharacter> KillerCharacterClass;
	UPROPERTY(EditAnywhere, Category = "GameMode",meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADBDCharacter> SurvivorCharacterClass;
};
