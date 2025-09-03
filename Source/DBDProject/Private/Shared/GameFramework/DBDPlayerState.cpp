// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/GameFramework/DBDPlayerState.h"

#include "JMS/GAS/SurvivorAttributeSet.h"
#include "KMJ/AbilitySystem/KillerAttributeSet.h"
#include "Shared/GAS/DBDAbilitySystemComponent.h"

ADBDPlayerState::ADBDPlayerState()
{
	DBDAbilitySystemComponent = CreateDefaultSubobject<UDBDAbilitySystemComponent>("DBDAbilitySystemComponent");
	DBDAbilitySystemComponent->SetIsReplicated(true);
	NetUpdateFrequency = 100.0f;
	PlayerRole = EPlayerRole::Survivor;
}

UAbilitySystemComponent* ADBDPlayerState::GetAbilitySystemComponent() const
{
	return DBDAbilitySystemComponent;
}

EPlayerRole ADBDPlayerState::GetPlayerRole() const
{
	return PlayerRole;
}

EPlayerRole ADBDPlayerState::SetPlayerRole(EPlayerRole NewRole)
{
	PlayerRole = NewRole;
	return PlayerRole;
}

void ADBDPlayerState::InitAttributeSet()
{
	if (PlayerRole == EPlayerRole::Killer)
	{
		UKillerAttributeSet* KillerAttributeSet = NewObject<UKillerAttributeSet>(this);
		DBDAbilitySystemComponent->AddAttributeSetSubobject(KillerAttributeSet);
	}
	else
	{
		USurvivorAttributeSet* SurvivorAttributeSet = NewObject<USurvivorAttributeSet>(this);
		DBDAbilitySystemComponent->AddAttributeSetSubobject(SurvivorAttributeSet);
	}
}
