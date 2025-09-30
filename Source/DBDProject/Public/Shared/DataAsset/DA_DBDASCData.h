

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_DBDASCData.generated.h"

class UGameplayAbility;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDA_DBDASCData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category="GEs")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;

	// 초기 세팅 어빌리티
	UPROPERTY(EditDefaultsOnly, Category = "GA")
	TArray<TSubclassOf<UGameplayAbility>> InitializedAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "GA")
	TArray<TSubclassOf<UGameplayAbility>> PassiveAbilities;

};
