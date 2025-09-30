// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheGameObjectSpawnManager.generated.h"

class AGeneratorPresetSpawner;

UCLASS()
class DBDPROJECT_API ATheGameObjectSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATheGameObjectSpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	int32 GeneratorCount;
	
	TArray<TArray<TArray<int32>>> GeneratorIndexArray;
	
	TArray<TArray<TArray<AGeneratorPresetSpawner*>>> GeneratorPresetSpawnerBlockArray;



private:
	void SetGeneratorIndexArray();
	void ExceptionAndInsertGeneratorIndex(int32 XSpawnIndex, int32 YSpawnIndex, int32 ZSpawnIndex);
	//void DebugGeneratorIndexArray();
	void GeneratorSpawn();
	//이건 나중에 공통 액터 정렬 로직으로도 사용 가능성이 있어보임
	TArray<AActor*> QuickSortActorByLocation(const TArray<AActor*>& SortTargetArray);
	bool CompareActorLocation(AActor* Actor1, AActor* Actor2);
};
