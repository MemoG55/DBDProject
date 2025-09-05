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
#include "Shared/DataAsset/DBDDataBase.h"
#include "Shared/GAS/DBDAbilitySystemComponent.h"

ADBDPlayerState::ADBDPlayerState()
{
	DBDAbilitySystemComponent = CreateDefaultSubobject<UDBDAbilitySystemComponent>("DBDAbilitySystemComponent");
	DBDAbilitySystemComponent->SetIsReplicated(true);
	DBDAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
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

void ADBDPlayerState::AuthInitAttributeSet()
{
	if (!HasAuthority())
	{
		return;
	}
	if (PlayerRole == EPlayerRole::Killer)
	{
		UKillerAttributeSet* KillerAttributeSet = NewObject<UKillerAttributeSet>(this);
		DBDAbilitySystemComponent->AddAttributeSetSubobject(KillerAttributeSet);
		//TObjectPtr<UKillerAbilitySystemComponent> KillerAbilitySystemComponent = CreateDefaultSubobject<UKillerAbilitySystemComponent>("KillerAbilitySystemComponent");
		UHuntressAttributeSet* HuntressAttributeSet = NewObject<UHuntressAttributeSet>(this);
		DBDAbilitySystemComponent->AddAttributeSetSubobject(HuntressAttributeSet);
	}
	else
	{
		USurvivorAttributeSet* SurvivorAttributeSet = NewObject<USurvivorAttributeSet>(this);
		DBDAbilitySystemComponent->AddAttributeSetSubobject(SurvivorAttributeSet);
	}
}

void ADBDPlayerState::AuthInitPerks()
{
	if (!HasAuthority())
	{
		return;
	}

	ADBDCharacter* DBDCharacter = GetPawn<ADBDCharacter>();
	if (!DBDCharacter)
	{
		return;
	}

	const FPrimaryAssetId DBDAssetId(TEXT("DBDDataBase"), TEXT("DBDDataBase"));
	UDBDDataBase* DBDDataBase = Cast<UDBDDataBase>(UAssetManager::Get().GetPrimaryAssetObject(DBDAssetId));
	if (!DBDDataBase)
	{
		return;
	}

	if (PlayerRole == EPlayerRole::Survivor)
	{
		UDataTable* DT = Cast<UDataTable>(
			UAssetManager::Get().GetStreamableManager().LoadSynchronous(
				DBDDataBase->SurvivorPerkDB.ToSoftObjectPath()));
		if (DT)
		{
			DBDCharacter->InitializePerks(*DT, SurvivorLoadout.Perk1, SurvivorLoadout.Perk2,
			                              SurvivorLoadout.Perk3, SurvivorLoadout.Perk4);
		};
	}
}

void ADBDPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void ADBDPlayerState::OnRep_SurvivorLoadout()
{
}

void ADBDPlayerState::OnRep_KillerLoadout()
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
