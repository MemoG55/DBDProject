// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EndPlayerController.generated.h"

class UDBDHUD_EndGame;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API AEndPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AEndPlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void GetSeamlessTravelActorList(bool bToEntry, TArray<class AActor*>& ActorList) override;

	virtual void OnRep_PlayerState() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UDBDHUD_EndGame> EndHUDClass;
	
	UPROPERTY()
	TObjectPtr<UDBDHUD_EndGame> EndHUD;

public:
	UFUNCTION(Server, Reliable)
	void RequestExit();
	
};
