// Fill out your copyright notice in the Description page of Project Settings.

// DBDPlayerState를 참고해서 캐릭터를 스폰합니다.
// TODO: DBDPlayerState의 Loadout정보에서 스폰할 캐릭터의 키 값을 가져와서, 데이터베이스를 조회해서 해당 클래스를 스폰
// TODO: 초기화에 사용할 각종 데이터들이 담긴 데이터테이블을 DBDDataBase 클래스에 추가해주세요
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DBDGameMode.generated.h"

class ADBDGameStateBase;
class UDBDDataBase;
class AObjectSpawnerManager;
class ADBDCharacter;

/**
 * 
 */
UCLASS()
class DBDPROJECT_API ADBDGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ADBDGameMode();
	
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	

#pragma region GameFlow:
	// MMJ : 게임 종료조건 판단 함수

	UPROPERTY()
	ADBDGameStateBase* DBDGameState;
	
	// 게임 종료 조건 판단
	UFUNCTION()
	void CheckGameCondition();

	// 게임 종료
	UFUNCTION()
	void EndGameState();

	UFUNCTION()
	void MoveToEndLevel();

	// 탈출 타이머 UI 보여주기
	UFUNCTION(BlueprintCallable)
	void DisplayEscapeWidget(bool IsDisplay);
#pragma endregion
	
private:
	UPROPERTY(EditAnywhere, Category = "GameMode",meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADBDCharacter> KillerCharacterClass;
	UPROPERTY(EditAnywhere, Category = "GameMode",meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADBDCharacter> SurvivorCharacterClass;
};
