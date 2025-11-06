

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Containers/Map.h"
#include "Shared/DBDEnum.h"
#include "DA_SurvivorASCData.generated.h"

class UGameplayEffect;
class UGameplayAbility;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FInputAbilityInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	ESurvivorAbilityInputID AbilityID = ESurvivorAbilityInputID::None;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayAbility> AbilityClass = nullptr;
};

UCLASS()
class DBDPROJECT_API UDA_SurvivorASCData : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, Category = "GA")
	TArray<FInputAbilityInfo> InputAbilities;
	UPROPERTY(EditAnywhere)
	float MaxHookHP = 100;
	UPROPERTY(EditAnywhere)
	float MaxDyingHP = 100;
	UPROPERTY(EditAnywhere)
	float MaxHealProgress = 100;
	UPROPERTY(EditAnywhere)
	float MovementSpeed = 226;
	UPROPERTY(EditAnywhere)
	float SprintSpeed = 400;
	UPROPERTY(EditAnywhere)
	float CrouchSpeed = 113;
	UPROPERTY(EditAnywhere)
	float CrawlSpeed = 70;
	UPROPERTY(EditAnywhere)
	float InteractSpeed_Generator = 1;
	UPROPERTY(EditAnywhere)
	float InteractSpeed_ExitDoor = 1;
	UPROPERTY(EditAnywhere)
	float InteractSpeed_Chest = 1;
	UPROPERTY(EditAnywhere)
	float InteractSpeed_TotemCleansing= 1;
	UPROPERTY(EditAnywhere)
	float HealSpeed = 6.25;
	UPROPERTY(EditAnywhere)
	float HookSabotageSpeed = 1;
	UPROPERTY(EditAnywhere)
	float RescueSpeed = 1;
	UPROPERTY(EditAnywhere)
	float SkillCheckFrequency = 1;
	UPROPERTY(EditAnywhere)
	float QuickActionSoundVolume = 1;
	UPROPERTY(EditAnywhere)
	float CurrentItemCharge = 0;
	UPROPERTY(EditAnywhere)
	float MaxItemCharge = 0;
	UPROPERTY(EditDefaultsOnly, Category= "DT")
	UDataTable* SurvivorStatDataTable;
	UPROPERTY(EditDefaultsOnly, Category= "Survivor Effect")
	TSubclassOf<UGameplayEffect> ExhaustEffect;
};
