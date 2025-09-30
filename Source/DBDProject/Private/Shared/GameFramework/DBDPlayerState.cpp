// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/GameFramework/DBDPlayerState.h"

#include "Engine/AssetManager.h"
#include "JMS/GAS/SurvivorAttributeSet.h"
#include "KMJ/AbilitySystem/HuntressAttributeSet.h"
#include "KMJ/AbilitySystem/KillerAbilitySystemComponent.h"
#include "KMJ/AbilitySystem/KillerAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "Shared/DBDEnum.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/Controller/DBDPlayerController.h"
//#include "Shared/DataAsset/DBDDataBase.h"
#include "JMS/GAS/SurvivorAbilitySystemComponent.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/DataAsset/DBDDataBase.h"
#include "Shared/GAS/DBDAbilitySystemComponent.h"

ADBDPlayerState::ADBDPlayerState()
{
	NetUpdateFrequency = 100.0f;
	PlayerRole = EPlayerRole::Survivor;
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

ADBDCharacter* ADBDPlayerState::GetPlayerCharacter()
{
	if (ADBDPlayerController* PC = Cast<ADBDPlayerController>(GetOwner()))
	{
		if (ADBDCharacter* Character = Cast<ADBDCharacter>(PC->GetPawn()))
		{
			return Character;
		}
	}
	return nullptr;
}

bool ADBDPlayerState::GetPlayerStatusByTag(FGameplayTag Tag)
{
	if (GetPlayerCharacter())
	{
		return GetPlayerCharacter()->GetAbilitySystemComponent()->HasMatchingGameplayTag(Tag);
	}
	return false;
}

void ADBDPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void ADBDPlayerState::OnRep_SurvivorLoadout(FSurvivorLoadout OldLoadout)
{
}

void ADBDPlayerState::OnRep_KillerLoadout(FKillerLoadout OldLoadout)
{
}

void ADBDPlayerState::OnRep_PlayerRole()
{
}

void ADBDPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(ADBDPlayerState, SurvivorLoadout, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ADBDPlayerState, KillerLoadout, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ADBDPlayerState, PlayerRole, COND_None, REPNOTIFY_Always);
}
