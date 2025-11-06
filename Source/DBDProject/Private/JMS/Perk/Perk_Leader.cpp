// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Perk/Perk_Leader.h"

#include "Shared/DBDDebugHelper.h"
#include "Shared/Subsystem/DBDCharacterObserver.h"


UPerk_Leader::UPerk_Leader()
{
	PerkID = FName(TEXT("Leader"));
}

void UPerk_Leader::OnServerSideInitialized()
{
	Super::OnServerSideInitialized();
	UDBDCharacterObserver* CharacterObserver = GetWorld()->GetSubsystem<UDBDCharacterObserver>();
	if (!CharacterObserver)
	{
		//Debug::Print(TEXT("JMS11111:CharacterObserver is null"), 11111);
		return;
	}

	CharacterObserver->ApplyGEToSurvivorsWithinDistance(GetOuterAsDBDCharacter(), 800,
														 LeaderEffect);
}

void UPerk_Leader::OnOwnerClientSideInitialized()
{
	Super::OnOwnerClientSideInitialized();
}
