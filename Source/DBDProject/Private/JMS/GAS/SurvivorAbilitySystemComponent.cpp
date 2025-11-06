#include "JMS/GAS/SurvivorAbilitySystemComponent.h"

#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/DataAsset/DA_SurvivorASCData.h"
#include "JMS/GAS/AbilityPriorityInterface.h"
#include "JMS/GAS/SurvivorAttributeSet.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDStruct.h"

void USurvivorAbilitySystemComponent::GrantInputAbilities()
{
	if (GetOwner()->HasAuthority())
	{
		for (const FInputAbilityInfo& GAClassPair : SurvivorASCData->
		     InputAbilities)
		{
			// 어빌리티 레벨 = 0 (스킬 해금이 되지 않은 상태를 나타낼 때 사용 가능)
			GiveAbility(FGameplayAbilitySpec(GAClassPair.AbilityClass, 0, (int32)GAClassPair.AbilityID, nullptr));
		}
	}
}

void USurvivorAbilitySystemComponent::InitializeBaseAttributes()
{
	if (!SurvivorASCData)
	{
		//Debug::Print(TEXT("JMS10: SurvivorASCData is null"), 10);
		return;
	}
	// USurvivorAttributeSet
	SetNumericAttributeBase(USurvivorAttributeSet::GetMaxHookHPAttribute(), SurvivorASCData->MaxHookHP);
	SetNumericAttributeBase(USurvivorAttributeSet::GetMaxDyingHPAttribute(), SurvivorASCData->MaxDyingHP);
	SetNumericAttributeBase(USurvivorAttributeSet::GetMaxHealProgressAttribute(), SurvivorASCData->MaxHealProgress);
	SetNumericAttributeBase(USurvivorAttributeSet::GetMovementSpeedAttribute(), SurvivorASCData->MovementSpeed);
	SetNumericAttributeBase(USurvivorAttributeSet::GetSprintSpeedAttribute(), SurvivorASCData->SprintSpeed);
	SetNumericAttributeBase(USurvivorAttributeSet::GetCrouchSpeedAttribute(), SurvivorASCData->CrouchSpeed);
	SetNumericAttributeBase(USurvivorAttributeSet::GetCrawlSpeedAttribute(), SurvivorASCData->CrawlSpeed);
	SetNumericAttributeBase(USurvivorAttributeSet::GetInteractSpeed_GeneratorAttribute(),
	                        SurvivorASCData->InteractSpeed_Generator);
	SetNumericAttributeBase(USurvivorAttributeSet::GetInteractSpeed_ExitDoorAttribute(),
	                        SurvivorASCData->InteractSpeed_ExitDoor);
	SetNumericAttributeBase(USurvivorAttributeSet::GetInteractSpeed_ChestAttribute(),
	                        SurvivorASCData->InteractSpeed_Chest);
	SetNumericAttributeBase(USurvivorAttributeSet::GetInteractSpeed_TotemCleansingAttribute(),
	                        SurvivorASCData->InteractSpeed_TotemCleansing);
	SetNumericAttributeBase(USurvivorAttributeSet::GetHealSpeedAttribute(), SurvivorASCData->HealSpeed);
	SetNumericAttributeBase(USurvivorAttributeSet::GetHookSabotageSpeedAttribute(), SurvivorASCData->HookSabotageSpeed);
	SetNumericAttributeBase(USurvivorAttributeSet::GetRescueSpeedAttribute(), SurvivorASCData->RescueSpeed);
	SetNumericAttributeBase(USurvivorAttributeSet::GetSkillCheckFrequencyAttribute(),
	                        SurvivorASCData->SkillCheckFrequency);
	SetNumericAttributeBase(USurvivorAttributeSet::GetQuickActionSoundVolumeAttribute(),
	                        SurvivorASCData->QuickActionSoundVolume);
	SetNumericAttributeBase(USurvivorAttributeSet::GetCurrentItemChargeAttribute(), SurvivorASCData->CurrentItemCharge);
	SetNumericAttributeBase(USurvivorAttributeSet::GetMaxItemChargeAttribute(), SurvivorASCData->MaxItemCharge);


	if (!SurvivorASCData->SurvivorStatDataTable)
	{
		//Debug::Print(TEXT("JMS11: SurvivorASCData->SurvivorStatDataTable is null"), 11);
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

void USurvivorAbilitySystemComponent::ActivatePriorityAbilityByTag(FGameplayTag Tag)
{
	TArray<FGameplayAbilitySpec*> AbilitySpecArray;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(FGameplayTagContainer(Tag), AbilitySpecArray);
	TArray<FGameplayAbilitySpec*> HighestPriorityAbilities = FilterHighestPriorityAbilities(AbilitySpecArray);
	if (HighestPriorityAbilities.Num() > 0)
	{
		for (FGameplayAbilitySpec* Spec : HighestPriorityAbilities)
		{
			if (Spec->Handle.IsValid())
			{
				TryActivateAbility(Spec->Handle);
			}
			else
			{
				//Debug::Print(
				//	TEXT(
				//		"JMS1111111: USurvivorAbilitySystemComponent::ActivatePriorityAbilityByTag: Spec->Handle is not valid"),
				//	1111111);
			}
		}
	}
}

TArray<FGameplayAbilitySpec*> USurvivorAbilitySystemComponent::FilterHighestPriorityAbilities(
	const TArray<FGameplayAbilitySpec*>& InAbilitySpecs) const
{
	TArray<FGameplayAbilitySpec*> HighestPriorityAbilities;

	int32 MaxPriority = TNumericLimits<int32>::Min();
	bool bFoundAnyPrioritizedAbility = false;

	for (const FGameplayAbilitySpec* Spec : InAbilitySpecs)
	{
		if (Spec && Spec->Ability)
		{
			const IAbilityPriorityInterface* PriorityInterface = Cast<IAbilityPriorityInterface>(Spec->Ability.Get());

			if (PriorityInterface)
			{
				int32 CurrentPriority = PriorityInterface->GetPriority();
				MaxPriority = FMath::Max(MaxPriority, CurrentPriority);
				bFoundAnyPrioritizedAbility = true;
			}
		}
	}

	if (!bFoundAnyPrioritizedAbility)
	{
		return HighestPriorityAbilities;
	}

	for (FGameplayAbilitySpec* Spec : InAbilitySpecs)
	{
		if (Spec && Spec->Ability)
		{
			const IAbilityPriorityInterface* PriorityInterface = Cast<IAbilityPriorityInterface>(Spec->Ability.Get());

			if (PriorityInterface && PriorityInterface->GetPriority() == MaxPriority)
			{
				HighestPriorityAbilities.Add(Spec);
			}
		}
	}

	return HighestPriorityAbilities;
}
