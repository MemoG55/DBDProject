// Fill out your copyright notice in the Description page of Project Settings.

// UDBDGameInstance : UDBDDataBase* DBDDB에 Perk들에 대한 모든 데이터가 있습니다.
// Perk 장착 정보 : DBDPlayerState - Survivor/KillerLoadout구조체
// DBDCharacter의 PossessedBy에서 실제 PerkComponent가 생성
// 게임이 시작할 때 서버 : OnServerSideInitialized(), 클라이언트 : OnOwnerClientSideInitialized()가 호출됩니다.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PerkComponent.generated.h"

class ADBDCharacter;
class UPerkComponent;
/**
 * 
 */


UCLASS(Blueprintable)
class DBDPROJECT_API UPerkComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPerkComponent();
	virtual void OnServerSideInitialized();
	virtual void OnOwnerClientSideInitialized();
	FName GetPerkID();

protected:
	// Perk을 소유한 캐릭터를 반환합니다.
	ADBDCharacter* GetOuterAsDBDCharacter();

private:
	// UPROPERTY(ReplicatedUsing=OnRep_AfterServerInit)
	// bool bIsReplicatedAfterServerInitialization = false;
	// UFUNCTION()
	// void OnRep_AfterServerInit();

protected:
	UPROPERTY(EditDefaultsOnly,Category = "Perk")
	FName PerkID;
	// virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
