// Fill out your copyright notice in the Description page of Project Settings.
// 로비에서 설정하게 될 Loadout 정보를 담고 있습니다.
// Loadout에는 FName으로 DataTable을 조회할 키값들을 갖고 있습니다.
// 인게임에서 Loadout 정보가 변경되면 (아이템 사용 등) 키값을 변경해서 로비로 돌아왔을 때 변경된 정보를 토대로 인벤토리를 업데이트 할 수 있도록 하려고 합니다.

// 플레이어의 역할을 Enum으로 갖고 있습니다.
// ADBDGameMode::PostLogin에서 들어온 순서에 따라 역할을 배정하고 ADBDGameMode::HandleStartingNewPlayer에서 역할에 따라 캐릭터를 스폰합니다.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "KMJ/AbilitySystem/KillerAttributeSet.h"
#include "Shared/DBDStruct.h"
#include "DBDPlayerState.generated.h"

enum class EPlayerRole: uint8;
class UDBDAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class DBDPROJECT_API ADBDPlayerState : public APlayerState/*, public IAbilitySystemInterface*/
{
	GENERATED_BODY()
private:
	ADBDPlayerState();
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_PlayerRole, Category = "PlayerRole")
	EPlayerRole PlayerRole;

public:
	UFUNCTION(BlueprintCallable, Category = "PlayerRole")
	EPlayerRole GetPlayerRole() const;
	
	UFUNCTION(BlueprintCallable, Category = "PlayerRole")
	EPlayerRole SetPlayerRole(EPlayerRole NewRole);

	// MMJ : 플레이어 반환
	UFUNCTION(BlueprintCallable, Category = "GameFlow")
	ADBDCharacter* GetPlayerCharacter();
	// MMJ : 플레이어가 태그를 가지고 있는지 판별 (GameMode에서 Dead/Escape 상태 체크용)
	UFUNCTION(BlueprintCallable, Category = "GameFlow")
	bool GetPlayerStatusByTag(FGameplayTag Tag);
	

protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere,ReplicatedUsing=OnRep_SurvivorLoadout, Category = "Loadout")
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
protected:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
