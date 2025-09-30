// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/Spawner/Object/TheGameObjectSpawnManager.h"

#include "Kismet/GameplayStatics.h"
#include "YHG/Spawner/Object/GeneratorPresetSpawner.h"
#include "YHG/Spawner/Tile/TheGameTileSpawnManager.h"

#define MapExtent 4
#define MapHeight 2

// Sets default values
ATheGameObjectSpawnManager::ATheGameObjectSpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//0이 지상 1이 지하
	GeneratorIndexArray.SetNum(MapExtent);
	for (int32 Iterator = 0; Iterator < GeneratorIndexArray.Num(); Iterator++)
	{
		GeneratorIndexArray[Iterator].SetNum(MapExtent);
		for (int32 Iterator2 = 0; Iterator2 < GeneratorIndexArray[Iterator].Num(); Iterator2++)
		{
			GeneratorIndexArray[Iterator][Iterator2].SetNum(MapHeight);
			for (int32 Iterator3 = 0; Iterator3 < GeneratorIndexArray[Iterator][Iterator2].Num(); Iterator3++)
			{
				GeneratorIndexArray[Iterator][Iterator2][Iterator3] = 0;
			}
		}
	}

	//고정 컨트롤 룸 발전기 가중치 설정
	GeneratorIndexArray[0][0][0] = 2;
	GeneratorIndexArray[0][0][1] = 1000;
	
	GeneratorIndexArray[0][1][0] = 1;
	GeneratorIndexArray[0][1][1] = 2;

	GeneratorIndexArray[1][0][0] = 1;
	GeneratorIndexArray[1][0][1] = 2;

	GeneratorIndexArray[0][2][1] = 1;

	GeneratorIndexArray[2][0][1] = 1;
}

// Called when the game starts or when spawned
void ATheGameObjectSpawnManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (!HasAuthority())
		return;
	
	SetGeneratorIndexArray();

	//DebugGeneratorIndexArray();

	//타일 스폰 끝났을 때 호출되는 델리게이트 바인드
	AActor* TheGameTileSpawnManagerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ATheGameTileSpawnManager::StaticClass());
	ATheGameTileSpawnManager* TheGameTileSpawnManager = Cast<ATheGameTileSpawnManager>(TheGameTileSpawnManagerActor);
	if (!TheGameTileSpawnManager)
	{
		UE_LOG(LogTemp, Error, TEXT("TheGameTileSpawnManager is NULL"));
		return;
	}
	TheGameTileSpawnManager->OnFinishedTileSpawnDelegate.BindUObject(this, &ThisClass::GeneratorSpawn);
}

// Called every frame
void ATheGameObjectSpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATheGameObjectSpawnManager::SetGeneratorIndexArray()
{
	int32 XSpawnIndex = 0;
	int32 YSpawnIndex = 0;
	int32 ZSpawnIndex = 0;
	float AllowSpawnRandNum = 0.f;
	
	for (int32 Iterator = 0; Iterator < GeneratorCount; Iterator++)
	{
		XSpawnIndex = FMath::RandRange(0, GeneratorIndexArray.Num() - 1);
		YSpawnIndex = FMath::RandRange(0, GeneratorIndexArray[0].Num() - 1);
		ZSpawnIndex = FMath::RandRange(0, GeneratorIndexArray[0][0].Num() - 1);
		
		if (GeneratorIndexArray[XSpawnIndex][YSpawnIndex][ZSpawnIndex] >= 3)
		{
			Iterator--;
			continue;
		}
		//가중치가 2일 때는, 10%확률
		else if (GeneratorIndexArray[XSpawnIndex][YSpawnIndex][ZSpawnIndex] == 2)
		{
			AllowSpawnRandNum = FMath::FRand();
			if (AllowSpawnRandNum >= 0.1f)
			{
				Iterator--;
				continue;
			}
			else
			{
				ExceptionAndInsertGeneratorIndex(XSpawnIndex, YSpawnIndex, ZSpawnIndex);
			}
		}
		//가중치가 1일 때는 25%확률
		else if (GeneratorIndexArray[XSpawnIndex][YSpawnIndex][ZSpawnIndex] == 1)
		{
			AllowSpawnRandNum = FMath::FRand();
			if (AllowSpawnRandNum >= 0.25f)
			{
				Iterator--;
				continue;
			}
			else
			{
				ExceptionAndInsertGeneratorIndex(XSpawnIndex, YSpawnIndex, ZSpawnIndex);
			}
		}
		//0이면 항상 스폰 가능
		else
		{
			ExceptionAndInsertGeneratorIndex(XSpawnIndex, YSpawnIndex, ZSpawnIndex);
		}
	}
}

void ATheGameObjectSpawnManager::ExceptionAndInsertGeneratorIndex(int32 XSpawnIndex, int32 YSpawnIndex, int32 ZSpawnIndex)
{
	GeneratorIndexArray[XSpawnIndex][YSpawnIndex][ZSpawnIndex] += 100;
				
	if (XSpawnIndex > 0)
		GeneratorIndexArray[XSpawnIndex - 1][YSpawnIndex][ZSpawnIndex] += 2;
	if (XSpawnIndex > 1)
		GeneratorIndexArray[XSpawnIndex - 2][YSpawnIndex][ZSpawnIndex] += 1;
	
	if (XSpawnIndex < GeneratorIndexArray.Num() - 1)
		GeneratorIndexArray[XSpawnIndex + 1][YSpawnIndex][ZSpawnIndex] += 2;
	if (XSpawnIndex < GeneratorIndexArray.Num() - 2)
		GeneratorIndexArray[XSpawnIndex + 2][YSpawnIndex][ZSpawnIndex] += 1;
	
	if (YSpawnIndex > 0)
		GeneratorIndexArray[XSpawnIndex][YSpawnIndex - 1][ZSpawnIndex] += 2;
	if (YSpawnIndex > 1)
		GeneratorIndexArray[XSpawnIndex][YSpawnIndex - 2][ZSpawnIndex] += 1;
	
	if (YSpawnIndex < GeneratorIndexArray[0].Num() - 1)
		GeneratorIndexArray[XSpawnIndex][YSpawnIndex + 1][ZSpawnIndex] += 2;
	if (YSpawnIndex < GeneratorIndexArray[0].Num() - 2)
		GeneratorIndexArray[XSpawnIndex][YSpawnIndex + 2][ZSpawnIndex] += 1;
	
	//지상에 발전기 스폰 시 지하 가중치 처리
	if (ZSpawnIndex == 0)
	{
		GeneratorIndexArray[XSpawnIndex][YSpawnIndex][ZSpawnIndex + 1] += 2;
		
		if (XSpawnIndex > 0)
			GeneratorIndexArray[XSpawnIndex - 1][YSpawnIndex][ZSpawnIndex + 1] += 1;
		if (XSpawnIndex < GeneratorIndexArray.Num() - 1)
			GeneratorIndexArray[XSpawnIndex + 1][YSpawnIndex][ZSpawnIndex + 1] += 1;
		
		if (YSpawnIndex > 0)
			GeneratorIndexArray[XSpawnIndex][YSpawnIndex - 1][ZSpawnIndex + 1] += 1;
		if (YSpawnIndex < GeneratorIndexArray[0].Num() - 1)
			GeneratorIndexArray[XSpawnIndex][YSpawnIndex + 1][ZSpawnIndex + 1] += 1;
	}
	//지하에 발전기 스폰 시 지상 가중치 처리
	else
	{
		GeneratorIndexArray[XSpawnIndex][YSpawnIndex][ZSpawnIndex - 1] += 2;
		
		if (XSpawnIndex > 0)
			GeneratorIndexArray[XSpawnIndex - 1][YSpawnIndex][ZSpawnIndex - 1] += 1;
		if (XSpawnIndex < GeneratorIndexArray.Num() - 1)
			GeneratorIndexArray[XSpawnIndex + 1][YSpawnIndex][ZSpawnIndex - 1] += 1;
		
		if (YSpawnIndex > 0)
			GeneratorIndexArray[XSpawnIndex][YSpawnIndex - 1][ZSpawnIndex - 1] += 1;
		if (YSpawnIndex < GeneratorIndexArray[0].Num() - 1)
			GeneratorIndexArray[XSpawnIndex][YSpawnIndex + 1][ZSpawnIndex - 1] += 1;
	}
}
/*
void ATheGameObjectSpawnManager::DebugGeneratorIndexArray()
{
	
	//디버그
	for (int32 Iterator = 0; Iterator < GeneratorIndexArray.Num(); Iterator++)
	{
		for (int32 Iterator2 = 0; Iterator2 < GeneratorIndexArray[Iterator].Num(); Iterator2++)
		{
			for (int32 Iterator3 = 0; Iterator3 < GeneratorIndexArray[Iterator][Iterator2].Num(); Iterator3++)
			{
				UE_LOG(LogTemp, Warning, TEXT("%d "), GeneratorIndexArray[Iterator][Iterator2][Iterator3]);
			}
		}
	}
}*/

void ATheGameObjectSpawnManager::GeneratorSpawn()
{
	TArray<AActor*> GeneratorPresetSpawnerArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGeneratorPresetSpawner::StaticClass(), GeneratorPresetSpawnerArray);
	
	/*1번 코드 : 언리얼 자체 정렬 사용
	TArray<AActor*> SortedActors = GeneratorPresetSpawnerArray; // 원본 보존
	SortedActors.Sort([](AActor& A, AActor& B) {
		const FVector& LocationA = A.GetActorLocation();
		const FVector& LocationB = B.GetActorLocation();

		return (LocationA.X > LocationB.X ||
				(LocationA.X == LocationB.X && LocationA.Y < LocationB.Y) ||
				(LocationA.X == LocationB.X && LocationA.Y == LocationB.Y && LocationA.Z > LocationB.Z));
	});
	
	GeneratorPresetSpawnerBlockArray.SetNum(MapExtent);
	for (int32 Iterator = 0; Iterator < GeneratorPresetSpawnerBlockArray.Num(); Iterator++)
	{
		GeneratorPresetSpawnerBlockArray[Iterator].SetNum(MapExtent);
		for (int32 Iterator2 = 0; Iterator2 < GeneratorPresetSpawnerBlockArray[Iterator].Num(); Iterator2++)
		{
			GeneratorPresetSpawnerBlockArray[Iterator][Iterator2].SetNum(MapHeight);
			for (int32 Iterator3 = 0; Iterator3 < GeneratorPresetSpawnerBlockArray[Iterator][Iterator2].Num(); Iterator3++)
			{
				GeneratorPresetSpawnerBlockArray[Iterator][Iterator2][Iterator3] = nullptr;
			}
		}
	}

	int32 InsertCount = 0;
	for (int32 Iterator = 0; Iterator < GeneratorPresetSpawnerBlockArray.Num(); Iterator++)
	{
		for (int32 Iterator2 = 0; Iterator2 < GeneratorPresetSpawnerBlockArray[Iterator].Num(); Iterator2++)
		{
			for (int32 Iterator3 = 0; Iterator3 < GeneratorPresetSpawnerBlockArray[Iterator][Iterator2].Num(); Iterator3++)
			{
				if (Iterator == 0 && Iterator2 == 0 && Iterator3 == 1)
				{
					continue;
				}
				else
				{
					GeneratorPresetSpawnerBlockArray[Iterator][Iterator2][Iterator3] = Cast<AGeneratorPresetSpawner>(SortedActors[InsertCount++]);
				}
			}
		}
	}

	for (int32 Iterator = 0; Iterator < GeneratorPresetSpawnerBlockArray.Num(); Iterator++)
	{
		for (int32 Iterator2 = 0; Iterator2 < GeneratorPresetSpawnerBlockArray[Iterator].Num(); Iterator2++)
		{
			for (int32 Iterator3 = 0; Iterator3 < GeneratorPresetSpawnerBlockArray[Iterator][Iterator2].Num(); Iterator3++)
			{
				if (GeneratorIndexArray[Iterator][Iterator2][Iterator3] >= 100 && GeneratorIndexArray[Iterator][Iterator2][Iterator3] < 1000)
				{
					GeneratorPresetSpawnerBlockArray[Iterator][Iterator2][Iterator3]->SpawnGeneratorPreset();
				}
			}
		}
	}*/
	
	
	//2번 코드 : 퀵 정렬 직접 구현
	GeneratorPresetSpawnerArray = QuickSortActorByLocation(GeneratorPresetSpawnerArray);
	
	GeneratorPresetSpawnerBlockArray.SetNum(MapExtent);
	for (int32 Iterator = 0; Iterator < GeneratorPresetSpawnerBlockArray.Num(); Iterator++)
	{
		GeneratorPresetSpawnerBlockArray[Iterator].SetNum(MapExtent);
		for (int32 Iterator2 = 0; Iterator2 < GeneratorPresetSpawnerBlockArray[Iterator].Num(); Iterator2++)
		{
			GeneratorPresetSpawnerBlockArray[Iterator][Iterator2].SetNum(MapHeight);
			for (int32 Iterator3 = 0; Iterator3 < GeneratorPresetSpawnerBlockArray[Iterator][Iterator2].Num(); Iterator3++)
			{
				GeneratorPresetSpawnerBlockArray[Iterator][Iterator2][Iterator3] = nullptr;
			}
		}
	}
	
	int32 InsertCount = 0;
	for (int32 Iterator = 0; Iterator < GeneratorPresetSpawnerBlockArray.Num(); Iterator++)
	{
		for (int32 Iterator2 = 0; Iterator2 < GeneratorPresetSpawnerBlockArray[Iterator].Num(); Iterator2++)
		{
			for (int32 Iterator3 = 0; Iterator3 < GeneratorPresetSpawnerBlockArray[Iterator][Iterator2].Num(); Iterator3++)
			{
				if (Iterator == 0 && Iterator2 == 0 && Iterator3 == 1)
				{
					continue;
				}
				else
				{
					GeneratorPresetSpawnerBlockArray[Iterator][Iterator2][Iterator3] = Cast<AGeneratorPresetSpawner>(GeneratorPresetSpawnerArray[InsertCount++]);
				}
			}
		}
	}

	for (int32 Iterator = 0; Iterator < GeneratorPresetSpawnerBlockArray.Num(); Iterator++)
	{
		for (int32 Iterator2 = 0; Iterator2 < GeneratorPresetSpawnerBlockArray[Iterator].Num(); Iterator2++)
		{
			for (int32 Iterator3 = 0; Iterator3 < GeneratorPresetSpawnerBlockArray[Iterator][Iterator2].Num(); Iterator3++)
			{
				if (GeneratorIndexArray[Iterator][Iterator2][Iterator3] >= 100 && GeneratorIndexArray[Iterator][Iterator2][Iterator3] < 1000)
				{
					GeneratorPresetSpawnerBlockArray[Iterator][Iterator2][Iterator3]->SpawnGeneratorPreset();
				}
			}
		}
	}

	/*for (int32 Iterator = 0; Iterator < GeneratorPresetSpawnerBlockArray.Num(); Iterator++)
	{
		for (int32 Iterator2 = 0; Iterator2 < GeneratorPresetSpawnerBlockArray[Iterator].Num(); Iterator2++)
		{
			for (int32 Iterator3 = 0; Iterator3 < GeneratorPresetSpawnerBlockArray[Iterator][Iterator2].Num(); Iterator3++)
			{
				if (GeneratorPresetSpawnerBlockArray[Iterator][Iterator2][Iterator3] != nullptr)
				{
					UE_LOG(LogTemp, Warning, TEXT("%s "), *GeneratorPresetSpawnerBlockArray[Iterator][Iterator2][Iterator3]->GetActorNameOrLabel());
				}
			}
		}
	}*/
}

TArray<AActor*> ATheGameObjectSpawnManager::QuickSortActorByLocation(const TArray<AActor*>& SortTargetArray)
{
	
	
	if (SortTargetArray.Num() < 2) return SortTargetArray;

	int32 PivotIndex = FMath::RandRange(0, SortTargetArray.Num() - 1);
	TArray<AActor*> LeftArray;
	TArray<AActor*> RightArray;

	for (int32 Iterator = 0; Iterator < SortTargetArray.Num(); Iterator++)
	{
		if (Iterator == PivotIndex) continue; // 피벗 제외

		if (CompareActorLocation(SortTargetArray[Iterator], SortTargetArray[PivotIndex]))
		{
			LeftArray.Add(SortTargetArray[Iterator]);
		}
		else
		{
			RightArray.Add(SortTargetArray[Iterator]);
		}
	}

	LeftArray = QuickSortActorByLocation(LeftArray);
	RightArray = QuickSortActorByLocation(RightArray);

	LeftArray.Add(SortTargetArray[PivotIndex]);
	LeftArray.Append(RightArray);

	return LeftArray;
}

bool ATheGameObjectSpawnManager::CompareActorLocation(AActor* Actor1, AActor* Actor2)
{
	const FVector& LocationA = Actor1->GetActorLocation();
	const FVector& LocationB = Actor2->GetActorLocation();
	
	return (LocationA.X > LocationB.X ||
		(LocationA.X == LocationB.X && LocationA.Y < LocationB.Y) ||
		(LocationA.X == LocationB.X && LocationA.Y == LocationB.Y && LocationA.Z > LocationB.Z));
}