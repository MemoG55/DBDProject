// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "EntitySpawner.generated.h"

class AObj_Entity;

USTRUCT(BlueprintType)
struct FEntitySpawnInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag EntityTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AObj_Entity> EntityClass;
};

/*
 * Entity의 스폰을 전담하는 액터
 */
UCLASS()
class DBDPROJECT_API AEntitySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEntitySpawner();
	
	UFUNCTION()
	AObj_Entity* SpawnEntity(class ADBDObject* OwnerObject, FGameplayTag EntityTag);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "EntityInfo")
	TArray<FEntitySpawnInfo> EntityInfos;

	UFUNCTION()
	TSubclassOf<AObj_Entity> GetEntityInfo(FGameplayTag EntityTag);
};
