// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Shared/DBDEnum.h"
#include "LobbyPlayerController.generated.h"

struct FItemAddonData;
struct FItemData;
struct FPerkData;
class ULobbyLoadOutSlot;
class ULobbyHUD;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ALobbyPlayerController();
protected:
	virtual void BeginPlay() override;

public:
	virtual void GetSeamlessTravelActorList(bool bToEntry, TArray<AActor*>& ActorList) override;

	virtual void OnRep_PlayerState() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ULobbyHUD> LobbyHUDClass;
	
	UPROPERTY()
	TObjectPtr<ULobbyHUD> LobbyHUD;

	UFUNCTION(Server, Reliable)
	void SetReady();

	UFUNCTION(Server, Reliable)
	void SetRole();
	
	UFUNCTION(Server, Reliable)
	void SetLoadOut(ELobbyLoadOutSlotType SlotType);

	UFUNCTION(Server, Reliable)
	void SetLoadOutPerk(const FName& DataRowName, const FPerkData& SourceData);

	UFUNCTION(Server, Reliable)
	void SetLoadOutItem(const FName& DataRowName, const FItemData& SourceData);

	UFUNCTION(Server, Reliable)
	void SetLoadOutAddOn(const FName& DataRowName, const FItemAddonData& SourceData);

	UFUNCTION(Server, Reliable)
	void SetCharacterMesh(const FString& SelectString, ESelectInfo::Type SelectionType);
};
