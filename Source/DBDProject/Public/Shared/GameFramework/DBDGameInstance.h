// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedFriendsGameInstance.h"
#include "Shared/DBDStruct.h"
#include "DBDGameInstance.generated.h"

/**
 * 
 */

struct FStreamableHandle;
class AGenericObjectPool;
class APoolEntry_ScratchMark;
class UDBDDataBase;
enum class EPlayerRole: uint8;

USTRUCT()
struct FDBDPlayerStateData
{
	GENERATED_BODY()

	UPROPERTY()
	EPlayerRole PlayerRole = EPlayerRole::Killer;

	UPROPERTY()
	FSurvivorLoadout SurvivorLoadout = FSurvivorLoadout();

	UPROPERTY()
	FKillerLoadout KillerLoadout = FKillerLoadout();
};

UCLASS()
class DBDPROJECT_API UDBDGameInstance : public UAdvancedFriendsGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataBase")
	UDBDDataBase* DBDDB;

	UPROPERTY()
	TObjectPtr<UDBDDataBase> LoadedDB;

	UPROPERTY()
	TArray<TObjectPtr<UDataTable>> LoadedTables;

	UPROPERTY()
	TMap<FUniqueNetIdRepl, FDBDPlayerStateData> PlayerStateMaps;

	TSharedPtr<FStreamableHandle> DatabaseLoadHandle;
	TSharedPtr<FStreamableHandle> SecondaryDatabaseLoadHandle;
	TSharedPtr<FStreamableHandle> AssetLoadHandle;

	UPROPERTY(Transient)
	TArray<UTexture2D*> AssetTextures;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> LoadingScreenClass;
	UPROPERTY()
	UUserWidget* LoadingScreenInstance;
private:
	// 데이터베이스 로딩
	void StartDatabaseLoading();
	void OnDatabaseLoaded(FPrimaryAssetId LoadedId);

	// 두번째 데이터테이블 로딩
	void SecondaryDatabaseLoading(UDBDDataBase* DB);
	void OnSecondaryDatabaseLoaded(UDBDDataBase* DB);

	// 데이터테이블 내 SoftObjectPath 에셋 로딩
	void SecondaryAssetLoading(TArray<UDataTable*> DataTables);
	void OnAllSecondaryAssetLoaded(TArray<UDataTable*> DataTables);
	
	void StartLoadingScreen(const FString& MapName);
	void EndLoadingScreen(UWorld* LoadedWorld);
};
