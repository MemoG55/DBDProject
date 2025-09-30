// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable/DBDObject.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "TestSurvivor.generated.h"

class ADBDPlayerController;
class ADBDObject;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API ATestSurvivor : public ASurvivorCharacter
{
	GENERATED_BODY()
public:
	UPROPERTY()
	ADBDObject* CachedCurrentInteractObject;

	UFUNCTION()
	APlayerController* GetPlayerController();
	
	UFUNCTION(BlueprintCallable)
	void TryInteract(bool& Result);

	UFUNCTION(BlueprintCallable)
	void CancelInteract();
	
	UFUNCTION(Server, Reliable)
	void Server_Interact(ADBDObject* Object);

	UFUNCTION(BlueprintCallable)
	void Client_Interact(ADBDObject* Object);

	UFUNCTION(Server, Reliable)
	void Server_Disconnect(ADBDObject* Object);

	UFUNCTION(BlueprintCallable)
	void SetCanInteract(bool Result);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCanInteract = false;

	UFUNCTION(BlueprintCallable)
	void GetSurvivor();

	UPROPERTY()
	ADBDCharacter* Survivor;

	UFUNCTION(Server, Reliable)
	void SetSurvivor(ADBDCharacter* Actor);


	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};