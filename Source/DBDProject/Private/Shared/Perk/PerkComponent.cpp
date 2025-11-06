// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Perk/PerkComponent.h"

#include "Net/UnrealNetwork.h"
#include "Shared/Character/DBDCharacter.h"


UPerkComponent::UPerkComponent()
{
	SetIsReplicatedByDefault(true);
}

void UPerkComponent::OnServerSideInitialized()
{
	// bIsReplicatedAfterServerInitialization = true;
}

void UPerkComponent::OnOwnerClientSideInitialized()
{
}

FName UPerkComponent::GetPerkID()
{
	return PerkID;
}

ADBDCharacter* UPerkComponent::GetOuterAsDBDCharacter()
{
	return CastChecked<ADBDCharacter>(GetOuter());
}

// void UPerkComponent::OnRep_AfterServerInit()
// {
// 	if (GetOwnerRole() == ROLE_AutonomousProxy)
// 	{
// 		OnOwnerClientSideInitialized();
// 	}
// }
//
// void UPerkComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
// {
// 	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
// 	DOREPLIFETIME_CONDITION_NOTIFY(UPerkComponent, bIsReplicatedAfterServerInitialization, COND_None, REPNOTIFY_Always);
// }
