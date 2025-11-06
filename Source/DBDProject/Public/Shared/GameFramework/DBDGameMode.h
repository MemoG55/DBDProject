// Fill out your copyright notice in the Description page of Project Settings.

// DBDPlayerState�참고�캐릭�� �폰�니
// TODO: DBDPlayerStateLoadout�보�서 �폰캐릭�의 값을 가�� �이�베�스�조���당 �래�� �폰
// TODO: 초기�에 �용각종 �이�들�긴 �이�테�블DBDDataBase �래�에 추�주�
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "DBDGameMode.generated.h"

struct FStreamableHandle;
class ASurvivorCharacter;
class ADBDPlayerState;
class ADBDGameStateBase;
class UDBDDataBase;
class AObjectSpawnerManager;
class ADBDCharacter;
class APlayerStart;

/**
 * 
 */
UCLASS()
class DBDPROJECT_API ADBDGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ADBDGameMode();

	virtual void StartPlay() override;
protected:
	virtual void BeginPlay() override;
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	virtual void HandleSeamlessTravelPlayer(AController*& C) override;
	virtual void GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList) override;
	virtual void PostSeamlessTravel() override;

	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName = L"") override;

	void StartInGameAssetLoading();

	void OnInGameAssetLoaded();

	void StartAsyncLoading(const TArray<FSoftObjectPath>& AssetsToLoad);
	TSharedPtr<FStreamableHandle> InGameAssetLoadHandle;
	
	UFUNCTION()
	void CharacterInit();

	//YHG: MaxPlayer's num
	UPROPERTY(EditDefaultsOnly)
	int32 MaxPlayerCount;
	//YHG : 
	UPROPERTY()
	FTransform KillerSpawnTransform;
	UPROPERTY()
	TArray<TObjectPtr<APlayerStart>> SurvivorPlayerStarts;
	int32 SurvivorSpawnCurrentIndex;

#pragma region GameFlow:
	// MMJ : 

	UPROPERTY()
	ADBDGameStateBase* DBDGameState;

	// Survivor Tag Delegate
	UFUNCTION()
	void OnSurvivorTagChange(struct FGameplayTag Tag, int32 Count);
	// Killer Tag Delegate
	UFUNCTION()
	void OnKillerTagChange(FGameplayTag Tag, int32 Count);
	// Final End Condition Check
	UFUNCTION()
	void CheckGameCondition();
	// 게임 종료
	UFUNCTION()
	void EndGameState();
	// ServerTravel
	UFUNCTION()
	void MoveToEndLevel();
	// 발전기 수리 완료 시 (탈출구 개방 or Only Aura)
	UFUNCTION()
	void OnGeneratorComplete(AActor* Object, AActor* Interactor);
	// 발전기 수리 작용 시 (Aura)
	UFUNCTION()
	void OnGeneratorInteract(AActor* Object, AActor* Interactor);

	UFUNCTION()
	void SetEscapeTimer();

#pragma endregion
	
private:
	UPROPERTY(EditAnywhere, Category = "GameMode",meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADBDCharacter> KillerCharacterClass;
	// UPROPERTY(EditAnywhere, Category = "GameMode",meta = (AllowPrivateAccess = "true"))
	// TSubclassOf<ADBDCharacter> SurvivorCharacterClass;

	ASurvivorCharacter* SpawnSurvivorCharacter(ADBDPlayerState* DBDPS, FTransform SpawnTransform);
};

