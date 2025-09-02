// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/GameFramework/DBDPlayerState.h"

#include "Shared/GAS/DBDAbilitySystemComponent.h"

ADBDPlayerState::ADBDPlayerState()
{
	DBDAbilitySystemComponent = CreateDefaultSubobject<UDBDAbilitySystemComponent>("DBDAbilitySystemComponent");
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
