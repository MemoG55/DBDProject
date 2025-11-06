// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/GameFramework/DBDGameInstance.h"

#include "Blueprint/UserWidget.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "JMS/ScratchMark/PoolEntry_ScratchMark.h"
#include "Shared/AssetManager/DBDAssetManager.h"
#include "Shared/DataAsset/DA_PreloadAssets.h"
#include "Shared/DataAsset/DBDDataBase.h"
#include "Shared/ObjectPool/GenericObjectPool.h"

void UDBDGameInstance::Init()
{
	Super::Init();

	StartDatabaseLoading();
	
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &ThisClass::StartLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ThisClass::EndLoadingScreen);
}

void UDBDGameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);
	
}

void UDBDGameInstance::StartDatabaseLoading()
{
	// JMS: 미리 로딩�셋 추�
	FPrimaryAssetId DatabaseAssetId("DBDDataBase", FName(TEXT("DBDDB")));
	FPrimaryAssetId PreloadAssetId("DA_PreloadAssets", FName(TEXT("DA_PreloadAssets")));
	TArray<FPrimaryAssetId> AssetsToLoad;
	AssetsToLoad.Add(DatabaseAssetId);
	AssetsToLoad.Add(PreloadAssetId);

	UDBDAssetManager& DBDAssetManager = UDBDAssetManager::Get();
	
	AssetLoadHandle = DBDAssetManager.LoadPrimaryAssets(
		AssetsToLoad,
		TArray<FName>(),
		FStreamableDelegate::CreateUObject(this, &UDBDGameInstance::OnDatabaseLoaded, DatabaseAssetId)
		);

}

void UDBDGameInstance::OnDatabaseLoaded(FPrimaryAssetId LoadedId)
{
	UDBDAssetManager& DBDAssetManager = UDBDAssetManager::Get();
	UDBDDataBase* DB = Cast<UDBDDataBase>(DBDAssetManager.GetPrimaryAssetObject(LoadedId));
	if (DB)
	{
		LoadedDB = DB;
	}
	SecondaryDatabaseLoading(DB);
	AssetLoadHandle.Reset();
}

void UDBDGameInstance::SecondaryDatabaseLoading(UDBDDataBase* DB)
{
	if (!DB) return;

	TArray<FSoftObjectPath> SecondaryDataBaseToLoad;

	TArray<TSoftObjectPtr<UDataTable>> AllDataTables = {
		DB->SurvivorPerkDB,
		DB->KillerPerkDB,
		DB->SurvivorItemDB,
		DB->ItemAddonDB,
		DB->SurvivorCharacterDB
	};
	for (TSoftObjectPtr<UDataTable> DataTable : AllDataTables)
	{
		SecondaryDataBaseToLoad.Add(DataTable.ToSoftObjectPath());
	}

	if (SecondaryDataBaseToLoad.Num() > 0)
	{
		UDBDAssetManager& DBDAssetManager = UDBDAssetManager::Get();
		
		SecondaryDatabaseLoadHandle = DBDAssetManager.GetStreamableManager().RequestAsyncLoad(
			SecondaryDataBaseToLoad,
			FStreamableDelegate::CreateUObject(this, &UDBDGameInstance::OnSecondaryDatabaseLoaded, DB)
		);
	}
}

void UDBDGameInstance::OnSecondaryDatabaseLoaded(UDBDDataBase* DB)
{
	LoadedTables.Empty();
	LoadedTables.Add(DB->SurvivorCharacterDB.Get());
	LoadedTables.Add(DB->SurvivorPerkDB.Get());
	LoadedTables.Add(DB->KillerPerkDB.Get());
	LoadedTables.Add(DB->SurvivorItemDB.Get());
	LoadedTables.Add(DB->ItemAddonDB.Get());
	SecondaryAssetLoading(LoadedTables);
	SecondaryDatabaseLoadHandle.Reset();
}

void UDBDGameInstance::SecondaryAssetLoading(TArray<UDataTable*> DataTables)
{
	TArray<FSoftObjectPath> SecondaryAssetsToLoad;


	for (const UDataTable* DataTable : DataTables)
	{
		if (!DataTable) continue;

		TArray<FName> RowNames = DataTable->GetRowNames();
		for (const FName& RowName : RowNames)
		{
			FSurvivorCharacterData* CharacterData = DataTable->FindRow<FSurvivorCharacterData>(RowName, TEXT("Load FSurvivorCharacterData Secondary Assets"));
			if (CharacterData)
			{
				SecondaryAssetsToLoad.Add(CharacterData->CharacterPortrait.ToSoftObjectPath());
			}

			FItemData* ItemData = DataTable->FindRow<FItemData>(RowName, TEXT("Load FItemData Secondary Assets"));
			if (ItemData)
			{
				SecondaryAssetsToLoad.Add(ItemData->Icon.ToSoftObjectPath());
			}

			FPerkData* PerkData = DataTable->FindRow<FPerkData>(RowName, TEXT("Load FPerkData Secondary Assets"));
			if (PerkData)
			{
				SecondaryAssetsToLoad.Add(PerkData->Icon.ToSoftObjectPath());
			}

			FItemAddonData* ItemAddonData = DataTable->FindRow<FItemAddonData>(RowName, TEXT("Load FItemAddonData Secondary Assets"));
			if (ItemAddonData)
			{
				SecondaryAssetsToLoad.Add(ItemAddonData->Icon.ToSoftObjectPath());
			}
		}
	}


	// JMS: 미리 로딩�셋
	FPrimaryAssetId PreloadAssetId("DA_PreloadAssets", FName(TEXT("DA_PreloadAssets")));
	UDA_PreloadAssets* PreloadAssets = Cast<UDA_PreloadAssets>(UAssetManager::Get().GetPrimaryAssetObject(PreloadAssetId));

	for (TSoftObjectPtr<UObject> ObjectPtr : PreloadAssets->AssetsToPreload)
	{
		SecondaryAssetsToLoad.Add(ObjectPtr.ToSoftObjectPath());
	}
	
	if (SecondaryAssetsToLoad.Num() > 0)
	{
		UDBDAssetManager& DBDAssetManager = UDBDAssetManager::Get();
		
		AssetLoadHandle = DBDAssetManager.GetStreamableManager().RequestAsyncLoad(
			SecondaryAssetsToLoad,
			FStreamableDelegate::CreateUObject(this, &UDBDGameInstance::OnAllSecondaryAssetLoaded, DataTables)
		);
	}
}

void UDBDGameInstance::OnAllSecondaryAssetLoaded(TArray<UDataTable*> DataTables)
{
	AssetTextures.Empty();
	
	for (const UDataTable* DataTable : DataTables)
	{
		if (!DataTable) continue;

		TArray<FName> RowNames = DataTable->GetRowNames();
		for (const FName& RowName : RowNames)
		{
			FSurvivorCharacterData* CharacterData = DataTable->FindRow<FSurvivorCharacterData>(RowName, TEXT("Load FSurvivorCharacterData Secondary Assets"));
			if (CharacterData)
			{
				AssetTextures.Add(CharacterData->CharacterPortrait.Get());
			}

			FItemData* ItemData = DataTable->FindRow<FItemData>(RowName, TEXT("Load FItemData Secondary Assets"));
			if (ItemData)
			{
				AssetTextures.Add(ItemData->Icon.Get());
			}

			FPerkData* PerkData = DataTable->FindRow<FPerkData>(RowName, TEXT("Load FPerkData Secondary Assets"));
			if (PerkData)
			{
				AssetTextures.Add(PerkData->Icon.Get());
			}

			FItemAddonData* ItemAddonData = DataTable->FindRow<FItemAddonData>(RowName, TEXT("Load FItemAddonData Secondary Assets"));
			if (ItemAddonData)
			{
				AssetTextures.Add(ItemAddonData->Icon.Get());
			}
		}
	}
	AssetLoadHandle.Reset();
}

void UDBDGameInstance::StartLoadingScreen(const FString& MapName)
{
	if (LoadingScreenClass)
	{
		LoadingScreenInstance = CreateWidget<UUserWidget>(this, LoadingScreenClass);
		if (LoadingScreenInstance)
		{
			LoadingScreenInstance->AddToViewport(100);
		}
	}
}

void UDBDGameInstance::EndLoadingScreen(UWorld* LoadedWorld)
{
	if (LoadingScreenInstance)
	{
		LoadingScreenInstance->RemoveFromParent();
		LoadingScreenClass = nullptr;
	}
}
