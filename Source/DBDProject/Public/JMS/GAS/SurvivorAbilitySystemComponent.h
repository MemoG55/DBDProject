#pragma once

#include "CoreMinimal.h"
#include "Shared/GAS/DBDAbilitySystemComponent.h"
#include "SurvivorAbilitySystemComponent.generated.h"


class UDA_SurvivorCommonStats;
class UDA_SurvivorASCData;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DBDPROJECT_API USurvivorAbilitySystemComponent : public UDBDAbilitySystemComponent
{
	GENERATED_BODY()

public:
	
	virtual void GrantInputAbilities() override;
	
	virtual void InitializeBaseAttributes() override;

	UPROPERTY(EditDefaultsOnly, Category = "DataControl")
	UDA_SurvivorASCData* SurvivorASCData;

	// Priority로 Ability 활성화 - 미사용중
	void ActivatePriorityAbilityByTag(FGameplayTag Tag);
protected:
	TArray<FGameplayAbilitySpec*> FilterHighestPriorityAbilities(const TArray<FGameplayAbilitySpec*>& InAbilitySpecs) const;
};
