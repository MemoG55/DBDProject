// Fill out your copyright notice in the Description page of Project Settings.
#include "Shared/GAS/DBDGlobalAbilitySystem.h"
#include "GameplayAbilitySpec.h"
#include "Abilities/GameplayAbility.h"
#include "Shared/GAS/DBDAbilitySystemComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(DBDGlobalAbilitySystem)

void FGlobalAppliedAbilityList::AddToASC(TSubclassOf<UGameplayAbility> Ability, UDBDAbilitySystemComponent* ASC)
{
	if (FGameplayAbilitySpecHandle* SpecHandle = Handles.Find(ASC))
	{
		RemoveFromASC(ASC);
	}

	UGameplayAbility* AbilityCDO = Ability->GetDefaultObject<UGameplayAbility>();
	FGameplayAbilitySpec AbilitySpec(AbilityCDO);
	const FGameplayAbilitySpecHandle AbilitySpecHandle = ASC->GiveAbility(AbilitySpec);
	Handles.Add(ASC, AbilitySpecHandle);
}

void FGlobalAppliedAbilityList::RemoveFromASC(UDBDAbilitySystemComponent* ASC)
{
	if (FGameplayAbilitySpecHandle* SpecHandle = Handles.Find(ASC))
	{
		ASC->ClearAbility(*SpecHandle);
		Handles.Remove(ASC);
	}
}

void FGlobalAppliedAbilityList::RemoveFromAll()
{
	for (auto& KVP : Handles)
	{
		if (KVP.Key != nullptr)
		{
			KVP.Key->ClearAbility(KVP.Value);
		}
	}
	Handles.Empty();
}



void FGlobalAppliedEffectList::AddToASC(TSubclassOf<UGameplayEffect> Effect, UDBDAbilitySystemComponent* ASC)
{
	if (FActiveGameplayEffectHandle* EffectHandle = Handles.Find(ASC))
	{
		RemoveFromASC(ASC);
	}

	const UGameplayEffect* GameplayEffectCDO = Effect->GetDefaultObject<UGameplayEffect>();
	const FActiveGameplayEffectHandle GameplayEffectHandle = ASC->ApplyGameplayEffectToSelf(GameplayEffectCDO, /*Level=*/ 1, ASC->MakeEffectContext());
	Handles.Add(ASC, GameplayEffectHandle);
}

void FGlobalAppliedEffectList::RemoveFromASC(UDBDAbilitySystemComponent* ASC)
{
	if (FActiveGameplayEffectHandle* EffectHandle = Handles.Find(ASC))
	{
		ASC->RemoveActiveGameplayEffect(*EffectHandle);
		Handles.Remove(ASC);
	}
}

void FGlobalAppliedEffectList::RemoveFromAll()
{
	for (auto& KVP : Handles)
	{
		if (KVP.Key != nullptr)
		{
			KVP.Key->RemoveActiveGameplayEffect(KVP.Value);
		}
	}
	Handles.Empty();
}

UDBDGlobalAbilitySystem::UDBDGlobalAbilitySystem()
{
}
#pragma region Killer
void UDBDGlobalAbilitySystem::ApplyAbilityToAllKiller(TSubclassOf<UGameplayAbility> Ability)
{
	if ((Ability.Get() != nullptr) && (!KillerAppliedAbilities.Contains(Ability)))
	{
		FGlobalAppliedAbilityList& Entry = KillerAppliedAbilities.Add(Ability);		
		for (UDBDAbilitySystemComponent* ASC : KillerRegisteredASCs)
		{
			Entry.AddToASC(Ability, ASC);
		}
	}
}

void UDBDGlobalAbilitySystem::ApplyEffectToAllKiller(TSubclassOf<UGameplayEffect> Effect)
{
	if ((Effect.Get() != nullptr) && (!KillerAppliedEffects.Contains(Effect)))
	{
		FGlobalAppliedEffectList& Entry = KillerAppliedEffects.Add(Effect);
		for (UDBDAbilitySystemComponent* ASC : KillerRegisteredASCs)
		{
			Entry.AddToASC(Effect, ASC);
		}
	}
}

void UDBDGlobalAbilitySystem::RemoveAbilityFromAllKiller(TSubclassOf<UGameplayAbility> Ability)
{
	if ((Ability.Get() != nullptr) && KillerAppliedAbilities.Contains(Ability))
	{
		FGlobalAppliedAbilityList& Entry = KillerAppliedAbilities[Ability];
		Entry.RemoveFromAll();
		KillerAppliedAbilities.Remove(Ability);
	}
}

void UDBDGlobalAbilitySystem::RemoveEffectFromAllKiller(TSubclassOf<UGameplayEffect> Effect)
{
	if ((Effect.Get() != nullptr) && KillerAppliedEffects.Contains(Effect))
	{
		FGlobalAppliedEffectList& Entry = KillerAppliedEffects[Effect];
		Entry.RemoveFromAll();
		KillerAppliedEffects.Remove(Effect);
	}
}

void UDBDGlobalAbilitySystem::RegisterKillerASC(UDBDAbilitySystemComponent* ASC)
{
	check(ASC);

	for (auto& Entry : KillerAppliedAbilities)
	{
		Entry.Value.AddToASC(Entry.Key, ASC);
	}
	for (auto& Entry : KillerAppliedEffects)
	{
		Entry.Value.AddToASC(Entry.Key, ASC);
	}

	KillerRegisteredASCs.AddUnique(ASC);
}

void UDBDGlobalAbilitySystem::UnregisterKillerASC(UDBDAbilitySystemComponent* ASC)
{
	check(ASC);
	for (auto& Entry : KillerAppliedAbilities)
	{
		Entry.Value.RemoveFromASC(ASC);
	}
	for (auto& Entry : KillerAppliedEffects)
	{
		Entry.Value.RemoveFromASC(ASC);
	}

	KillerRegisteredASCs.Remove(ASC);
}
#pragma endregion
#pragma region Survivor
void UDBDGlobalAbilitySystem::ApplyAbilityToAllSurvivor(TSubclassOf<UGameplayAbility> Ability)
{
	if ((Ability.Get() != nullptr) && (!SurvivorAppliedAbilities.Contains(Ability)))
	{
		FGlobalAppliedAbilityList& Entry = SurvivorAppliedAbilities.Add(Ability);		
		for (UDBDAbilitySystemComponent* ASC : SurvivorRegisteredASCs)
		{
			Entry.AddToASC(Ability, ASC);
		}
	}
}

void UDBDGlobalAbilitySystem::ApplyEffectToAllSurvivor(TSubclassOf<UGameplayEffect> Effect)
{
	if ((Effect.Get() != nullptr) && (!SurvivorAppliedEffects.Contains(Effect)))
	{
		FGlobalAppliedEffectList& Entry = SurvivorAppliedEffects.Add(Effect);
		for (UDBDAbilitySystemComponent* ASC : SurvivorRegisteredASCs)
		{
			Entry.AddToASC(Effect, ASC);
		}
	}
}

void UDBDGlobalAbilitySystem::RemoveAbilityFromAllSurvivor(TSubclassOf<UGameplayAbility> Ability)
{
	if ((Ability.Get() != nullptr) && SurvivorAppliedAbilities.Contains(Ability))
	{
		FGlobalAppliedAbilityList& Entry = SurvivorAppliedAbilities[Ability];
		Entry.RemoveFromAll();
		SurvivorAppliedAbilities.Remove(Ability);
	}
}

void UDBDGlobalAbilitySystem::RemoveEffectFromAllSurvivor(TSubclassOf<UGameplayEffect> Effect)
{
	if ((Effect.Get() != nullptr) && SurvivorAppliedEffects.Contains(Effect))
	{
		FGlobalAppliedEffectList& Entry = SurvivorAppliedEffects[Effect];
		Entry.RemoveFromAll();
		SurvivorAppliedEffects.Remove(Effect);
	}
}

void UDBDGlobalAbilitySystem::RegisterSurvivorASC(UDBDAbilitySystemComponent* ASC)
{
	check(ASC);

	for (auto& Entry : SurvivorAppliedAbilities)
	{
		Entry.Value.AddToASC(Entry.Key, ASC);
	}
	for (auto& Entry : SurvivorAppliedEffects)
	{
		Entry.Value.AddToASC(Entry.Key, ASC);
	}

	SurvivorRegisteredASCs.AddUnique(ASC);
}

void UDBDGlobalAbilitySystem::UnregisterSurvivorASC(UDBDAbilitySystemComponent* ASC)
{
	check(ASC);
	for (auto& Entry : SurvivorAppliedAbilities)
	{
		Entry.Value.RemoveFromASC(ASC);
	}
	for (auto& Entry : SurvivorAppliedEffects)
	{
		Entry.Value.RemoveFromASC(ASC);
	}

	SurvivorRegisteredASCs.Remove(ASC);
}
#pragma endregion
#pragma region Generator
void UDBDGlobalAbilitySystem::ApplyAbilityToAllGenerator(TSubclassOf<UGameplayAbility> Ability)
{
	if ((Ability.Get() != nullptr) && (!GeneratorAppliedAbilities.Contains(Ability)))
	{
		FGlobalAppliedAbilityList& Entry = GeneratorAppliedAbilities.Add(Ability);		
		for (UDBDAbilitySystemComponent* ASC : GeneratorRegisteredASCs)
		{
			Entry.AddToASC(Ability, ASC);
		}
	}
}

void UDBDGlobalAbilitySystem::ApplyEffectToAllGenerator(TSubclassOf<UGameplayEffect> Effect)
{
	if ((Effect.Get() != nullptr) && (!GeneratorAppliedEffects.Contains(Effect)))
	{
		FGlobalAppliedEffectList& Entry = GeneratorAppliedEffects.Add(Effect);
		for (UDBDAbilitySystemComponent* ASC : GeneratorRegisteredASCs)
		{
			Entry.AddToASC(Effect, ASC);
		}
	}
}

void UDBDGlobalAbilitySystem::RemoveAbilityFromAllGenerator(TSubclassOf<UGameplayAbility> Ability)
{
	if ((Ability.Get() != nullptr) && GeneratorAppliedAbilities.Contains(Ability))
	{
		FGlobalAppliedAbilityList& Entry = GeneratorAppliedAbilities[Ability];
		Entry.RemoveFromAll();
		GeneratorAppliedAbilities.Remove(Ability);
	}
}

void UDBDGlobalAbilitySystem::RemoveEffectFromAllGenerator(TSubclassOf<UGameplayEffect> Effect)
{
	if ((Effect.Get() != nullptr) && GeneratorAppliedEffects.Contains(Effect))
	{
		FGlobalAppliedEffectList& Entry = GeneratorAppliedEffects[Effect];
		Entry.RemoveFromAll();
		GeneratorAppliedEffects.Remove(Effect);
	}
}

void UDBDGlobalAbilitySystem::RegisterGeneratorASC(UDBDAbilitySystemComponent* ASC)
{
	check(ASC);

	for (auto& Entry : GeneratorAppliedAbilities)
	{
		Entry.Value.AddToASC(Entry.Key, ASC);
	}
	for (auto& Entry : GeneratorAppliedEffects)
	{
		Entry.Value.AddToASC(Entry.Key, ASC);
	}

	GeneratorRegisteredASCs.AddUnique(ASC);
}

void UDBDGlobalAbilitySystem::UnregisterGeneratorASC(UDBDAbilitySystemComponent* ASC)
{
	check(ASC);
	for (auto& Entry : GeneratorAppliedAbilities)
	{
		Entry.Value.RemoveFromASC(ASC);
	}
	for (auto& Entry : GeneratorAppliedEffects)
	{
		Entry.Value.RemoveFromASC(ASC);
	}

	GeneratorRegisteredASCs.Remove(ASC);
}
#pragma endregion