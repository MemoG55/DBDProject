// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/Spawner/Tile/TileSpawnManager.h"

#include "YHG/Spawner/Tile/CornerTileSpawner.h"
#include "YHG/Spawner/Tile/EdgeTileSpawner.h"
#include "YHG/Spawner/Tile/MidTileSpawner.h"

// Sets default values
ATileSpawnManager::ATileSpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	EscapeEdgeTileSpawnerIndexArrays.Add({0, 1}, {6, 7});
	EscapeEdgeTileSpawnerIndexArrays.Add({2, 3}, {4, 5});
	EscapeEdgeTileSpawnerIndexArrays.Add({4, 5}, {2, 3});
	EscapeEdgeTileSpawnerIndexArrays.Add({6, 7}, {0, 1});

	DoubleRoomEdgeTileIndexSelectArrays.Add({0, 0, 1});
	DoubleRoomEdgeTileIndexSelectArrays.Add({0, 1, 1});
}

// Called when the game starts or when spawned
void ATileSpawnManager::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		CornerTileSpawn();
		MidTileSpawn();
		EdgeTileSpawn();
	}
}

// Called every frame
void ATileSpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileSpawnManager::CornerTileSpawn()
{
	//중복 제거 선출
	int32 CornerRandomTileIndex;
	TArray<int32> CornerTileIndexArray;
	for (int32 Iterator = 0; Iterator < CornerTileSpawners.Num(); Iterator++)
	{
		CornerRandomTileIndex = FMath::RandRange(0, CornerTileSpawners[0]->GetTileActors().Num() - 1);
		if (CornerTileIndexArray.Contains(CornerRandomTileIndex))
		{
			Iterator--;
			continue;
		}
		CornerTileIndexArray.Add(CornerRandomTileIndex);
	}
	//타일 생성
	for (int32 Iterator = 0; Iterator < CornerTileIndexArray.Num(); Iterator++)
	{
		CornerTileSpawners[Iterator]->SpawnTile(CornerTileIndexArray[Iterator]);
	}
}

void ATileSpawnManager::EdgeTileSpawn()
{
	//탈출구 생성 : 스포너 중에서 랜덤으로 선정
	int32 EscapeEdgeRandomTileIndex = FMath::RandRange(0, EdgeTileSpawners.Num()-1);
	int32 EscapeEdgePairIndex = 0; 
	for (auto& Iterator : EscapeEdgeTileSpawnerIndexArrays)
	{
		if (Iterator.Key.Contains(EscapeEdgeRandomTileIndex))
		{
			EscapeEdgePairIndex = FMath::RandRange(Iterator.Value[0], Iterator.Value[1]);
		}
	}
	//탈출구 생성 : 실제 생성
	EdgeTileSpawners[EscapeEdgeRandomTileIndex]->SpawnEscapeTile(0);
	EdgeTileSpawners[EscapeEdgePairIndex]->SpawnEscapeTile(1);

	//더블 룸 생성
	//2개의 프리셋 중 랜덤으로 하나가 선택되어 2개가 배치되며, 나머지 1개의 프리셋은 1개만 배치된다
	//2개의 프리셋에서 3개의 방을 만드는 셈

	//먼저 2번 나올 방이 무엇인지 선택
	bool SelectDoubleRoomTile = FMath::RandBool();

	int32 DoubleRoomEdgeRandomTileIndex = 0;
	TArray<int32> DoubleRoomEdgeTileIndexArray;
	//다음은 EscapeRoom을 제외하고, 나머지 스포너 중에서 무작위로 3개 고르기
	for (int32 Iterator = 0; Iterator < DoubleRoomEdgeTileIndexSelectArrays[0].Num(); Iterator++)
	{
		DoubleRoomEdgeRandomTileIndex = FMath::RandRange(0, EdgeTileSpawners.Num()-1);
		if (DoubleRoomEdgeRandomTileIndex == EscapeEdgeRandomTileIndex ||
			DoubleRoomEdgeRandomTileIndex == EscapeEdgePairIndex ||
			DoubleRoomEdgeTileIndexArray.Contains(DoubleRoomEdgeRandomTileIndex))
		{
			Iterator--;
			continue;
		}
		DoubleRoomEdgeTileIndexArray.Add(DoubleRoomEdgeRandomTileIndex);
	}
	for (int32 Iterator = 0; Iterator < DoubleRoomEdgeTileIndexArray.Num(); Iterator++)
	{
		EdgeTileSpawners[DoubleRoomEdgeTileIndexArray[Iterator]]->SpawnDoubleRoomTile(DoubleRoomEdgeTileIndexSelectArrays[SelectDoubleRoomTile][Iterator]);
	}
	
	//마지막으로 NormalEdge 방 배치
	int32 EdgeRandomTileIndex = 0;
	TArray<int32> EdgeTileIndexArray;
	for (int32 Iterator = 0; Iterator < EdgeTileSpawners[0]->GetTileActors().Num(); Iterator++)
	{
		EdgeRandomTileIndex = FMath::RandRange(0, EdgeTileSpawners.Num()-1);
		if (EdgeRandomTileIndex == EscapeEdgeRandomTileIndex ||
			EdgeRandomTileIndex == EscapeEdgePairIndex ||
			DoubleRoomEdgeTileIndexArray.Contains(EdgeRandomTileIndex) ||
			EdgeTileIndexArray.Contains(EdgeRandomTileIndex))
		{
			Iterator--;
			continue;
		}
		EdgeTileIndexArray.Add(EdgeRandomTileIndex);
	}
	for (int32 Iterator = 0; Iterator < EdgeTileIndexArray.Num(); Iterator++)
	{
		EdgeTileSpawners[EdgeTileIndexArray[Iterator]]->SpawnTile(Iterator);
	}
}

void ATileSpawnManager::MidTileSpawn()
{
	//중복 제거 선출
	int32 MidRandomTileIndex;
	TArray<int32> MidTileIndexArray;
	for (int32 Iterator = 0; Iterator < MidTileSpawners.Num(); Iterator++)
	{
		MidRandomTileIndex = FMath::RandRange(0, MidTileSpawners[0]->GetTileActors().Num() - 1);
		if (MidTileIndexArray.Contains(MidRandomTileIndex))
		{
			Iterator--;
			continue;
		}
		MidTileIndexArray.Add(MidRandomTileIndex);
	}
	//타일 생성
	for (int32 Iterator = 0; Iterator < MidTileIndexArray.Num(); Iterator++)
	{
		MidTileSpawners[Iterator]->SpawnTile(MidTileIndexArray[Iterator]);
	}
}

