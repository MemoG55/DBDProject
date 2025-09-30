// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Subsystem/DBDCharacterObserver.h"

#include "JMS/Character/SurvivorCharacter.h"
#include "KMJ/Character/KillerCharacter.h"
#include "Shared/DBDDebugHelper.h"


void UDBDCharacterObserver::RegisterKiller(AKillerCharacter* KillerCharacter)
{
	Killer = KillerCharacter;
}

void UDBDCharacterObserver::UnregisterKiller(AKillerCharacter* KillerCharacter)
{
	if (Killer == KillerCharacter)
	{
		Killer = nullptr;
	}
}

void UDBDCharacterObserver::RegisterSurvivor(ASurvivorCharacter* SurvivorCharacter)
{
	Survivors.Add(SurvivorCharacter);
}

void UDBDCharacterObserver::UnregisterSurvivor(ASurvivorCharacter* SurvivorCharacter)
{
	Survivors.Remove(SurvivorCharacter);
}

void UDBDCharacterObserver::PrintAllCharacter()
{
	if (Killer)
	{
		UE_LOG(LogTemp,Warning,TEXT("JMS : UDBDCharacterObserver : Killer : %s"), *Killer->GetName());
	}
	for (ASurvivorCharacter* Survivor : Survivors)
	{
		UE_LOG(LogTemp,Warning,TEXT("JMS : UDBDCharacterObserver : Survivor : %s"), *Survivor->GetName());
	}
}

AKillerCharacter* UDBDCharacterObserver::GetKiller()
{
	return Killer;
}

ASurvivorCharacter* UDBDCharacterObserver::GetSurvivorByIndex(int32 Index)
{
	return Survivors[Index];
}

TArray<TObjectPtr<ASurvivorCharacter>> UDBDCharacterObserver::GetSurvivors()
{
	return Survivors;
}
