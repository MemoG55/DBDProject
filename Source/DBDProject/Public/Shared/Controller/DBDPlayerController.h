// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DBDPlayerController.generated.h"

class UDBDAbilitySystemComponent;
class ADBDSpectatorCam;
class UCommonActivatableWidget;
class USoundCue;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API ADBDPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ADBDPlayerController();
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	ADBDSpectatorCam* SpectatorCam;
	UPROPERTY()
	float CurrentYaw;
public:
	void EnterSpectatorCam();
	void ExitSpectatorCam();
	UPROPERTY()
	bool bIsSetSpectatorCam = false;

	UFUNCTION(Client, Reliable)
	void DisplayProgressUI(UDBDAbilitySystemComponent* ASC);
protected:

	virtual void Tick(float DeltaSeconds) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LoadingWidgetClass;
	UUserWidget* LoadingWidget;
	UPROPERTY(EditDefaultsOnly)
	USoundCue* StartMusicCue;
	UPROPERTY()
	UAudioComponent* StartMusicAudioComponent;
public:
	virtual void AcknowledgePossession(class APawn* P) override;
	void StartAfterWait();
	

};
