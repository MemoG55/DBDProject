// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PerkInstance.generated.h"

class UPerkInstance;

USTRUCT(BlueprintType)
struct FPerkData : public FTableRowBase
{
	GENERATED_BODY()
	// 키 값 탐색용
	UPROPERTY(EditAnywhere)
	FName QueryName;

	// 표시 될 이름
	UPROPERTY(EditAnywhere)
	FText DisplayName;

	// 희귀도
	UPROPERTY(EditAnywhere)
	int32 Tier;

	// 스킬 설명
	UPROPERTY(EditAnywhere)
	FText Description;

	// 한마디(스토리)
	UPROPERTY(EditAnywhere)
	FText Lore;

	// 아이콘
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTexture2D> Icon;

	// 실제 퍽 클래스
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPerkInstance> PerkClass;
};

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UPerkInstance : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void OnInitialized();
};
