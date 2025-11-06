// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Perk/Perk_ProveThyself.h"

#include "AbilitySystemComponent.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/Subsystem/DBDCharacterObserver.h"


UPerk_ProveThyself::UPerk_ProveThyself()
{
	PerkID = FName(TEXT("ProveThyself"));
}

void UPerk_ProveThyself::OnServerSideInitialized()
{
	Super::OnServerSideInitialized();
	UDBDCharacterObserver* CharacterObserver = GetWorld()->GetSubsystem<UDBDCharacterObserver>();
	if (!CharacterObserver)
	{
		//Debug::Print(TEXT("JMS11111:CharacterObserver is null"), 11111);
		return;
	}
	
	CharacterObserver->ApplyGEWithSurvivorWithinDistance(GetOuterAsDBDCharacter(), 400,
	                                                     ProveThyselfEffect);
}

void UPerk_ProveThyself::OnOwnerClientSideInitialized()
{
	Super::OnOwnerClientSideInitialized();
}
