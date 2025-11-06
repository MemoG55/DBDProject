// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/AssetManager/DBDAssetManager.h"

UDBDAssetManager& UDBDAssetManager::Get()
{
	check(GEngine);
	UDBDAssetManager* Manager = Cast<UDBDAssetManager>(GEngine->AssetManager);
	if (!Manager)
	{
		// 이 시점에서 널 포인터 에러 발생
		checkf(Manager, TEXT("AssetManager is NOT initialized! Check DefaultEngine.ini.")); 
	}
	return *Manager;
}

void UDBDAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
}

void UDBDAssetManager::StartStaticMeshLoading()
{
	FString TargetPath = TEXT("/Game/Content/Assets/YHG");

	FARFilter AssetFilter;
	AssetFilter.PackagePaths.Add(*TargetPath);
	AssetFilter.ClassPaths.Add(UStaticMesh::StaticClass()->GetClassPathName());
	AssetFilter.ClassPaths.Add(USkeletalMesh::StaticClass()->GetClassPathName());
	AssetFilter.bRecursivePaths = true;

	TArray<FAssetData> AssetDatas;

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	AssetRegistryModule.Get().GetAssets(AssetFilter, AssetDatas);

	TArray<FSoftObjectPath> AssetsToLoad;
	for (const FAssetData& AssetData : AssetDatas)
	{
		// AssetData를 FSoftObjectPath로 변환하여 목록에 추가
		AssetsToLoad.Add(AssetData.GetSoftObjectPath()); 
	}
    
	// 4. 비동기 로드 시작
	if (AssetsToLoad.Num() > 0)
	{
		(AssetsToLoad);
	}
	
}
