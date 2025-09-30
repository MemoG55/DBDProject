// Fill out your copyright notice in the Description page of Project Settings.

// LyraStarterGame에 있던 LyraGlobalAbilitySystem 코드를 가져와서 작성하였습니다.
// Lyra에서는 게임 내 모든 LyraAbilitySystemComponent를 InitAbilityActorInfo시점에 등록하고, 한꺼번에 GE, GA를 적용/해제하는 함수가 있었습니다.
// 코드를 그대로 복사하여 살인마, 생존자, 오브젝트(일단 발전기만)를 분리해서 등록하고 관리하도록 만들었습니다.
// 각자 필요한 함수를 만들어주시고 함수에 대한 설명을 헤더에 주석으로 작성해주세요
// TODO: 각 타입별 ~AbilitySystemComponent에서 InitAbilityActorInfo 함수를 Override하여 타입에 맞는 Register~ASC 함수를 호출하여 이곳에 등록
// TODO: 다양한 오브젝트를 관리하는 방법이 필요
// TODO: 복사 붙여넣기했을 뿐이므로 리팩토링이 필요
#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayAbilitySpecHandle.h"
#include "Templates/SubclassOf.h"
#include "DBDGlobalAbilitySystem.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UDBDAbilitySystemComponent;
class UObject;
struct FActiveGameplayEffectHandle;
struct FFrame;
struct FGameplayAbilitySpecHandle;

USTRUCT()
struct FGlobalAppliedAbilityList
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<TObjectPtr<UDBDAbilitySystemComponent>, FGameplayAbilitySpecHandle> Handles;

	void AddToASC(TSubclassOf<UGameplayAbility> Ability, UDBDAbilitySystemComponent* ASC);
	void RemoveFromASC(UDBDAbilitySystemComponent* ASC);
	void RemoveFromAll();
};

USTRUCT()
struct FGlobalAppliedEffectList
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<TObjectPtr<UDBDAbilitySystemComponent>, FActiveGameplayEffectHandle> Handles;

	void AddToASC(TSubclassOf<UGameplayEffect> Effect, UDBDAbilitySystemComponent* ASC);
	void RemoveFromASC(UDBDAbilitySystemComponent* ASC);
	void RemoveFromAll();
};
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDBDGlobalAbilitySystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	UDBDGlobalAbilitySystem();
#pragma region Killer
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Lyra")
	void ApplyAbilityToAllKiller(TSubclassOf<UGameplayAbility> Ability);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Lyra")
	void ApplyEffectToAllKiller(TSubclassOf<UGameplayEffect> Effect);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Lyra")
	void RemoveAbilityFromAllKiller(TSubclassOf<UGameplayAbility> Ability);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Lyra")
	void RemoveEffectFromAllKiller(TSubclassOf<UGameplayEffect> Effect);

	/** Register an ASC with global system and apply any active global effects/abilities. */
	void RegisterKillerASC(UDBDAbilitySystemComponent* ASC);

	/** Removes an ASC from the global system, along with any active global effects/abilities. */
	void UnregisterKillerASC(UDBDAbilitySystemComponent* ASC);

private:
	UPROPERTY()
	TMap<TSubclassOf<UGameplayAbility>, FGlobalAppliedAbilityList> KillerAppliedAbilities;

	UPROPERTY()
	TMap<TSubclassOf<UGameplayEffect>, FGlobalAppliedEffectList> KillerAppliedEffects;

	UPROPERTY()
	TArray<TObjectPtr<UDBDAbilitySystemComponent>> KillerRegisteredASCs;
#pragma endregion
#pragma region Survivor
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Lyra")
	void ApplyAbilityToAllSurvivor(TSubclassOf<UGameplayAbility> Ability);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Lyra")
	void ApplyEffectToAllSurvivor(TSubclassOf<UGameplayEffect> Effect);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Lyra")
	void RemoveAbilityFromAllSurvivor(TSubclassOf<UGameplayAbility> Ability);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Lyra")
	void RemoveEffectFromAllSurvivor(TSubclassOf<UGameplayEffect> Effect);

	/** Register an ASC with global system and apply any active global effects/abilities. */
	void RegisterSurvivorASC(UDBDAbilitySystemComponent* ASC);

	/** Removes an ASC from the global system, along with any active global effects/abilities. */
	void UnregisterSurvivorASC(UDBDAbilitySystemComponent* ASC);

private:
	UPROPERTY()
	TMap<TSubclassOf<UGameplayAbility>, FGlobalAppliedAbilityList> SurvivorAppliedAbilities;

	UPROPERTY()
	TMap<TSubclassOf<UGameplayEffect>, FGlobalAppliedEffectList> SurvivorAppliedEffects;

	UPROPERTY()
	TArray<TObjectPtr<UDBDAbilitySystemComponent>> SurvivorRegisteredASCs;
#pragma endregion
#pragma region Generator
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Lyra")
	void ApplyAbilityToAllGenerator(TSubclassOf<UGameplayAbility> Ability);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Lyra")
	void ApplyEffectToAllGenerator(TSubclassOf<UGameplayEffect> Effect);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Lyra")
	void RemoveAbilityFromAllGenerator(TSubclassOf<UGameplayAbility> Ability);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Lyra")
	void RemoveEffectFromAllGenerator(TSubclassOf<UGameplayEffect> Effect);

	/** Register an ASC with global system and apply any active global effects/abilities. */
	void RegisterGeneratorASC(UDBDAbilitySystemComponent* ASC);

	/** Removes an ASC from the global system, along with any active global effects/abilities. */
	void UnregisterGeneratorASC(UDBDAbilitySystemComponent* ASC);

private:
	UPROPERTY()
	TMap<TSubclassOf<UGameplayAbility>, FGlobalAppliedAbilityList> GeneratorAppliedAbilities;

	UPROPERTY()
	TMap<TSubclassOf<UGameplayEffect>, FGlobalAppliedEffectList> GeneratorAppliedEffects;

	UPROPERTY()
	TArray<TObjectPtr<UDBDAbilitySystemComponent>> GeneratorRegisteredASCs;
#pragma endregion
};
