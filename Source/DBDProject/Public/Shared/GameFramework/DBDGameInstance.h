// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedFriendsGameInstance.h"
#include "DBDGameInstance.generated.h"

/**
 * 
 */

class UDBDDataBase;

UCLASS()
class DBDPROJECT_API UDBDGameInstance : public UAdvancedFriendsGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataBase")
	UDBDDataBase* DBDDB;
private:
};
