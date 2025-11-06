// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Perk/Perk_Empathy.h"

#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Subsystem/DBDCharacterObserver.h"
#include "UObject/FastReferenceCollector.h"


UPerk_Empathy::UPerk_Empathy()
{
	PerkID = FName(TEXT("Empathy"));
}

void UPerk_Empathy::OnServerSideInitialized()
{
	Super::OnServerSideInitialized();
}

void UPerk_Empathy::OnOwnerClientSideInitialized()
{
	Super::OnOwnerClientSideInitialized();
	
		///Debug::Print(TEXT("JMS11112: Empathy client init called"), GetOwnerRole(),11111);
	UDBDCharacterObserver* CharacterObserver = GetWorld()->GetSubsystem<UDBDCharacterObserver>();
	if (!CharacterObserver)
	{
		//Debug::Print(TEXT("JMS11111:CharacterObserver is null"), 11111);
		return;
	}
	FGameplayTagContainer RequiredTags;
	RequiredTags.AddTag(DBDGameplayTags::Survivor_Status_Injured);
	RequiredTags.AddTag(DBDGameplayTags::Survivor_Status_Dying);
	FGameplayTagContainer BlockedTags;
	BlockedTags.AddTag(DBDGameplayTags::Survivor_Status_Captured_Killer);
	BlockedTags.AddTag(DBDGameplayTags::Survivor_Status_Captured_Hook);

	CharacterObserver->EnableSurvivorAuraWithDistanceAndTag(GetOuterAsDBDCharacter(), 2000, RequiredTags, BlockedTags);
}


