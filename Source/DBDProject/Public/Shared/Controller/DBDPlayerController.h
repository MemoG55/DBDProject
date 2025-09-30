// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DBDPlayerController.generated.h"

class ADBDSpectatorCam;
class UCommonActivatableWidget;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API ADBDPlayerController : public APlayerController
{
	GENERATED_BODY()
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	ADBDSpectatorCam* SpectatorCam;
public:
	void EnterSpectatorCam();

	void CustomCreateWidget();
protected:
	// Server Only
	//virtual void OnPossess(APawn* InPawn) override;
public:

	// Client Only
	//virtual void AcknowledgePossession(class APawn* P) override;
};
