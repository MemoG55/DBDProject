#include "JMS/GAS/SurvivorAbilitySystemComponent.h"

#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/DataAsset/DA_SurvivorASCData.h"
#include "JMS/GAS/SurvivorAttributeSet.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDStruct.h"

void USurvivorAbilitySystemComponent::GrantInputAbilities()
{
	if (GetOwner()->HasAuthority())
	{
		for (const TPair<ESurvivorAbilityInputID, TSubclassOf<UGameplayAbility>>& GAClassPair : SurvivorASCData->
		     InputAbilities)
		{
			// 어빌리티 레벨 = 0 (스킬 해금이 되지 않은 상태를 나타낼 때 사용 가능)
			GiveAbility(FGameplayAbilitySpec(GAClassPair.Value, 0, (int32)GAClassPair.Key, nullptr));
		}
	}
}

void USurvivorAbilitySystemComponent::InitializeBaseAttributes()
{
	if (!SurvivorASCData)
	{
		Debug::Print(TEXT("JMS10: SurvivorASCData is null"), 10);
		return;
	}
	// USurvivorAttributeSet
	SetNumericAttributeBase(USurvivorAttributeSet::GetMaxHookHPAttribute(), SurvivorASCData->MaxHookHP);
	SetNumericAttributeBase(USurvivorAttributeSet::GetMaxDyingHPAttribute(), SurvivorASCData->MaxDyingHP);
	SetNumericAttributeBase(USurvivorAttributeSet::GetMaxHealProgressAttribute(), SurvivorASCData->MaxHealProgress);
	SetNumericAttributeBase(USurvivorAttributeSet::GetMovementSpeedAttribute(), SurvivorASCData->MovementSpeed);
	SetNumericAttributeBase(USurvivorAttributeSet::GetGeneratorRepairSpeedAttribute(),
	                        SurvivorASCData->GeneratorRepairSpeed);
	SetNumericAttributeBase(USurvivorAttributeSet::GetHealSpeedAttribute(), SurvivorASCData->HealSpeed);
	SetNumericAttributeBase(USurvivorAttributeSet::GetSkillCheckFrequencyAttribute(), SurvivorASCData->SkillCheckFrequency);


	if (!SurvivorASCData->SurvivorStatDataTable)
	{
		Debug::Print(TEXT("JMS11: SurvivorASCData->SurvivorStatDataTable is null"), 11);
		return;
	}
	const FSurvivorBaseStat* BaseStats = nullptr;


	for (const auto& DataPair : SurvivorASCData->SurvivorStatDataTable->GetRowMap())
	{
		BaseStats = SurvivorASCData->SurvivorStatDataTable->FindRow<FSurvivorBaseStat>(DataPair.Key, "");
		if (BaseStats && BaseStats->CharacterClass == GetOwner()->GetClass())
		{
			break;
		}
	}
	if (BaseStats)
	{
	}
}
