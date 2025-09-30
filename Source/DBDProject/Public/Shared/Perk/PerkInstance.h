// Fill out your copyright notice in the Description page of Project Settings.

// DBDGameMode에 Perk들에 대한 모든 데이터가 있습니다.
// 어떤 Perk을 장착했는지는 DBDPlayerState에 Loadout 구조체 안에 FName으로 표시되어 있습니다.
// DBDCharacter에 장착된 PerkInstance가 멤버로 들어있습니다.
// DBDCharacter의 PossessedBy에서 Loadout키값으로 데이터를 조회해서 PerkInstance를 생성합니다.
// 모든 PerkInstance는 생성시점에 OnInitialized()가 호출됩니다.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PerkInstance.generated.h"

class ADBDCharacter;
class UPerkInstance;
/**
 * 
 */


UCLASS()
class DBDPROJECT_API UPerkInstance : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnInitialized();
protected:
	// Perk을 소유한 캐릭터를 반환합니다.
	ADBDCharacter* GetOuterAsDBDCharacter();
};
