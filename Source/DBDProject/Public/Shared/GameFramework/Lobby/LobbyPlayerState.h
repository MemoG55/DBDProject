// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "LobbyPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReadyStateUpdatedToSelf);
/**
 * 
 */
UCLASS()
class DBDPROJECT_API ALobbyPlayerState : public ADBDPlayerState
{
	GENERATED_BODY()
	
public:
	FOnReadyStateUpdatedToSelf OnReadyStateUpdatedToSelf;
	
	
	UFUNCTION()
	void SetReady(bool NewValue);

	UFUNCTION()
	bool GetReady();

private:
	UPROPERTY(ReplicatedUsing = OnRep_IsReady)
	bool bIsReady;

	UFUNCTION()
	void OnRep_IsReady();

protected:
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	virtual void CopyProperties(APlayerState* PlayerState) override;


};
