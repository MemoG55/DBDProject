// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DBDCharacterObserver.generated.h"

/**
 * 
 */
class AKillerCharacter;
class ASurvivorCharacter;

UCLASS()
class DBDPROJECT_API UDBDCharacterObserver : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	void RegisterKiller(AKillerCharacter* KillerCharacter);
	void UnregisterKiller(AKillerCharacter* KillerCharacter);
	void RegisterSurvivor(ASurvivorCharacter* SurvivorCharacter);
	void UnregisterSurvivor(ASurvivorCharacter* SurvivorCharacter);

	void PrintAllCharacter();
	AKillerCharacter* GetKiller();
	ASurvivorCharacter* GetSurvivorByIndex(int32 Index);
	TArray<TObjectPtr<ASurvivorCharacter>> GetSurvivors();
protected:
	UPROPERTY()
	TObjectPtr<AKillerCharacter> Killer;
	UPROPERTY()
	TArray<TObjectPtr<ASurvivorCharacter>> Survivors;

	
	
};
