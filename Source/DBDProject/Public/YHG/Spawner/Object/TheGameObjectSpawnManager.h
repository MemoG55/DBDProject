// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheGameObjectSpawnManager.generated.h"

class AHookSpawner;
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

	//발전기 가중치 스폰 관련
private:
	UPROPERTY(EditDefaultsOnly)
	int32 GeneratorCount;
	
	TArray<TArray<TArray<int32>>> GeneratorIndexArray;
	
	TArray<TArray<TArray<AGeneratorPresetSpawner*>>> GeneratorPresetSpawnerBlockArray;
	
	void SetGeneratorIndexArray();
	void ExceptionAndInsertGeneratorIndex(int32 XSpawnIndex, int32 YSpawnIndex, int32 ZSpawnIndex);
	void GeneratorSpawn();
	TArray<AActor*> QuickSortActorByLocation(const TArray<AActor*>& SortTargetArray);
	bool CompareActorLocation(AActor* Actor1, AActor* Actor2);

	//후크 스폰 관련(발전기의 가중치를 이용)
private:
	//발전기 가중치 중에서 HookWeight 값 이상인 곳에 스폰
	//즉, HookWeight값이 낮을 수록 많이 스폰
	UPROPERTY(EditDefaultsOnly)
	int32 HookWeight;
	
	TArray<TArray<TArray<AHookSpawner*>>> HookSpawnerBlockArray;
	void HookSpawn();

	//판자는 그냥 랜덤으로
private:
	UPROPERTY(EditDefaultsOnly)
	int32 PalletCount;
	
	void PalletSpawn() const;
};
