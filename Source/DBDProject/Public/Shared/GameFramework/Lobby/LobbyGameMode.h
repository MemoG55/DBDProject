// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

struct FItemData;
struct FItemAddonData;
struct FPerkData;
class ADBDPlayerState;
enum class EPlayerRole : uint8;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ALobbyGameMode();
protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void OnPostLogin(AController* NewPlayer) override;

public:
	virtual void GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList) override;

	virtual void PostSeamlessTravel() override;
	// 플레이어의 역할 변경
	void HandlePlayerRole(ADBDPlayerState* CurrentPlayerState, EPlayerRole NewRole);

	void InitializePlayerRole(ADBDPlayerState* CurrentPlayerState, EPlayerRole NewRole);
	// 모든 플레이어가 레디상태가 되었을 때
	void OnAllPlayerIsReady();

	// 레디상태로 전환
	void HandlePlayerReadyState(ADBDPlayerState* CurrentPlayerState, bool bIsReady);

	// 로드아웃
	void HandleLoadOutPerk(ADBDPlayerState* CurrentPlayerState, const FName& SourceData);
	void HandleLoadOutItem(ADBDPlayerState* CurrentPlayerState, const FName& SourceData);
	void HandleLoadOutAddOn(ADBDPlayerState* CurrentPlayerState, const FName& SourceData);

	// 캐릭터 메쉬
	void HandleCharacterMesh(ADBDPlayerState* CurrentPlayerState, const FName& SourceData);
	
private:
	// 킬러가 배정되어있는 상태인지
	UFUNCTION()
	bool IsKillerExists();

	// 생존자가 모두 배정되었는지
	UFUNCTION()
	bool IsSurvivorFull();
	
	
	
};
