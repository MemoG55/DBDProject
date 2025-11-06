// Fill out your copyright notice in the Description page of Project Settings.
// 로비�서 �정�게 Loadout �보르고 �습�다.
// Loadout�는 FName�로 DataTable조회�값�을 갖고 �습�다.
// �게�에Loadout �보가 변경되�(�이�용  �값변경해로비롌아�을 변경된 �보률�롸벤�리륅데�트 �도롘려곩니

// �레�어��Enum�로 갖고 �습�다.
// ADBDGameMode::PostLogin�서 �어�서�라 ��배정�고 ADBDGameMode::HandleStartingNewPlayer�서 ���라 캐릭�� �폰�니
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Shared/DBDStruct.h"
#include "DBDPlayerState.generated.h"

enum class EPlayerRole: uint8;
class UDBDAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSurvivorLoadOutUpdatedToSelf);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKillerLoadOutUpdatedToSelf);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerRoleUpdatedToSelf);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerStateUpdatedToSelf);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateAddedToSelf, ADBDPlayerState*, NewPS);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerRoleUpdatedToOther, ADBDPlayerState*, CurrentPS);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSurvivorLoadOutUpdatedToOther, ADBDPlayerState*, CurrentPS);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKillerLoadOutUpdatedToOther, ADBDPlayerState*, CurrentPS);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateUpdatedToOther, ADBDPlayerState*, CurrentPS);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateUpdatedFromOther, ADBDPlayerState*, OtherPS);
/**
 * 
 */
UCLASS()
class DBDPROJECT_API ADBDPlayerState : public APlayerState/*, public IAbilitySystemInterface*/
{
	GENERATED_BODY()
public:
	ADBDPlayerState();

	// Bind for Self
	FOnSurvivorLoadOutUpdatedToSelf		OnSurvivorLoadOutUpdatedToSelf;
	FOnKillerLoadOutUpdatedToSelf		OnKillerLoadOutUpdatedToSelf;
	FOnPlayerRoleUpdatedToSelf			OnPlayerRoleUpdatedToSelf;
	// When Added PlayerState to GameState->PlayerArray, Notice To Self
	FOnPlayerStateAddedToSelf			OnPlayerStateAddedToSelf;

	// When Update My PlayerState, Notice To Other
	FOnPlayerStateUpdatedToOther		OnPlayerStateUpdatedToOther;
	FOnPlayerStateUpdatedToSelf			OnPlayerStateUpdatedToSelf;
	// When Update Other PlayerState, Notice To Self
	FOnPlayerStateUpdatedFromOther		OnPlayerStateUpdatedFromOther;
	
	// Bind for OtherActor
	// When Update My PlayerState, Notice To Other
	FOnPlayerRoleUpdatedToOther			OnPlayerRoleUpdatedToOther;
	FOnSurvivorLoadOutUpdatedToOther	OnSurvivorLoadOutUpdatedToOther;
	FOnKillerLoadOutUpdatedToOther		OnKillerLoadOutUpdatedToOther;

protected:
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_PlayerRole, Category = "PlayerRole")
	EPlayerRole PlayerRole;

	UPROPERTY(Replicated)
	EPlayerEndState PlayerEndState = EPlayerEndState::None;

public:
	UFUNCTION(BlueprintCallable, Category = "PlayerRole")
	EPlayerRole GetPlayerRole() const;
	
	UFUNCTION(BlueprintCallable, Category = "PlayerRole")
	EPlayerRole SetPlayerRole(EPlayerRole NewRole);

	UFUNCTION()
	EPlayerEndState GetPlayerEndState() const;
	UFUNCTION()
	void SetPlayerEndState(EPlayerEndState EndState = EPlayerEndState::None);
	
	// // JMS: Seamless Travel�서 �이�� 복사�는 �수것으�보임
	virtual void CopyProperties(APlayerState* PlayerState) override;
protected:
	virtual void BeginPlay() override;
public:
	//ReadWrite �시
	UPROPERTY(EditAnywhere,ReplicatedUsing=OnRep_SurvivorLoadout, Category = "Loadout", BlueprintReadWrite)
	FSurvivorLoadout SurvivorLoadout;
	UPROPERTY(EditAnywhere,ReplicatedUsing=OnRep_KillerLoadout, Category = "Loadout")
	FKillerLoadout KillerLoadout;
private:
	UFUNCTION()
	void OnRep_SurvivorLoadout(FSurvivorLoadout OldLoadout);
	UFUNCTION()
	void OnRep_KillerLoadout(FKillerLoadout OldLoadout);
	UFUNCTION()
	void OnRep_PlayerRole();

public:
	UFUNCTION()
	virtual void OnRep_OnPlayerStateAddedToSelf(ADBDPlayerState* NewPS);

	// if OtherPlayerStateChanged, This Function called
	UFUNCTION()
	void OnRep_OnPlayerStateUpdatedFromOther(ADBDPlayerState* OtherPS);
protected:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
