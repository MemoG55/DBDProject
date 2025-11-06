// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DBDHUD.h"
#include "Components/WidgetComponent.h"
#include "DBDWidgetComponent.generated.h"

enum class EPlayerRole : uint8;
class ADBDCharacter;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWidgetUpdateGeneratorCountDelegate, int32, RequiredGeneratorRepairCount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FWidgetUpdateAbilityProgressDelegate, bool, bIsVisible, FText,
                                               Description, float, Percentage);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWidgetUpdateAbilityNameOnlyWidgetDelegate, bool, bIsVisible, FText,
                                             Description);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWidgetUpdateEquippedItemChangedDelegate, ASurvivorItem*, NewItem);
UCLASS(Blueprintable)
class DBDPROJECT_API UDBDWidgetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDBDWidgetComponent();

private:
	virtual void BeginPlay() override;
	void LateWidgetInitialization();

public:
	// JMS: UI수정 : UI는 여기서만 관리
	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Widget)
	UPROPERTY()
	UDBDHUD* PlayerHUD;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Widget)
	TSubclassOf<UDBDHUD> PlayerHUDClass;

	// JMS: UI수정: InitializePerkWidget으로 변경
	// JMS: UI수정2: 안써도 될듯
	// UFUNCTION()
	// void SetPlayerHUD(ADBDCharacter* Character, EPlayerRole PlayerRole);
	// UFUNCTION()
	// void InitializePerkWidget();
	// JMS: UI수정: InitializeItemSkillWidget으로 변경
	// JMS: UI수정2: 안써도 될듯
	// UFUNCTION()
	// void SetPlayerItemSkillHUD(ADBDCharacter* Character, EPlayerRole PlayerRole);
	// UFUNCTION()
	// void InitializePlayerItemSkillWidget();
#pragma region WidgetDelegates
	FWidgetUpdateGeneratorCountDelegate OnUpdateGeneratorCount;
	FWidgetUpdateAbilityProgressDelegate OnUpdateAbilityProgress;
	FWidgetUpdateAbilityNameOnlyWidgetDelegate OnUpdateAbilityNameOnlyWidget;
	FWidgetUpdateEquippedItemChangedDelegate OnUpdateEquippedItem;
#pragma endregion

protected:
	// JMS: UI수정: UPROPERTY추가 - 없을 시 GC가 지워버릴 수 있음
	UPROPERTY()
	ADBDCharacter* PlayerCharacter = nullptr;
};
