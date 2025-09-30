

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_SurvivorASCData.generated.h"

class UGameplayAbility;
enum class ESurvivorAbilityInputID : uint8;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDA_SurvivorASCData : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, Category = "GA")
	TMap<ESurvivorAbilityInputID, TSubclassOf<UGameplayAbility>> InputAbilities;
	UPROPERTY(EditAnywhere)
	float MaxHookHP = 100;
	UPROPERTY(EditAnywhere)
	float MaxDyingHP = 100;
	UPROPERTY(EditAnywhere)
	float MaxHealProgress = 100;
	UPROPERTY(EditAnywhere)
	float MovementSpeed = 300;
	UPROPERTY(EditAnywhere)
	float GeneratorRepairSpeed = 1;
	UPROPERTY(EditAnywhere)
	float HealSpeed = 6.25;
	UPROPERTY(EditAnywhere)
	float SkillCheckFrequency = 1;
	UPROPERTY(EditDefaultsOnly, Category= "DT")
	UDataTable* SurvivorStatDataTable;
};
