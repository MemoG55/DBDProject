// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Character/DBDCharacter.h"
#include "AbilitySystemInterface.h"
#include "Net/UnrealNetwork.h"
#include "Shared/Animation/DBDAnimInstance.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/Perk/PerkInstance.h"

ADBDCharacter::ADBDCharacter()
{
	NetUpdateFrequency = 100.0f;
}

UAbilitySystemComponent* ADBDCharacter::GetAbilitySystemComponent() const
{
	IAbilitySystemInterface* PSASInterface = Cast<IAbilitySystemInterface>(GetPlayerState());
	if (PSASInterface)
	{
		return PSASInterface->GetAbilitySystemComponent();
	}
	return nullptr;
}

void ADBDCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!GetMesh())
	{
		return;
	}
	UDBDAnimInstance* DBDAnimInstance = Cast<UDBDAnimInstance>(GetMesh()->GetAnimInstance());
	if (DBDAnimInstance)
	{
		DBDAnimInstance->InitializeWithAbilitySystem(GetAbilitySystemComponent());
	}
	ADBDPlayerState* PS = Cast<ADBDPlayerState>(GetPlayerState());
	if (PS)
	{
		PS->AuthInitPerks();
	}
}

void ADBDCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if (!GetMesh())
	{
		return;
	}
	UDBDAnimInstance* DBDAnimInstance = Cast<UDBDAnimInstance>(GetMesh()->GetAnimInstance());
	if (DBDAnimInstance)
	{
		DBDAnimInstance->InitializeWithAbilitySystem(GetAbilitySystemComponent());
	}
}

void ADBDCharacter::InitializePerks(const UDataTable& DataTable, FName Perk1Name, FName Perk2Name, FName Perk3Name,
                                    FName Perk4Name)
{
	if (Perk1Name != NAME_None)
	{
		FPerkData* Perk1Data = DataTable.FindRow<FPerkData>(Perk1Name, "");
		if (Perk1Data)
		{
			TSubclassOf<UPerkInstance> Perk1Class = Perk1Data->PerkClass;
			if (Perk1Class)
			{
				UPerkInstance* Perk1Instance = NewObject<UPerkInstance>(this, Perk1Class);
				Perk1Instance->OnInitialized();
			}
		}
	}
	if (Perk2Name != NAME_None)
	{
		FPerkData* Perk2Data = DataTable.FindRow<FPerkData>(Perk2Name, "");
		if (Perk2Data)
		{
			TSubclassOf<UPerkInstance> Perk2Class = Perk2Data->PerkClass;
			if (Perk2Class)
			{
				UPerkInstance* Perk2Instance = NewObject<UPerkInstance>(this, Perk2Class);
				Perk2Instance->OnInitialized();
			}
		}
	}
	if (Perk3Name != NAME_None)
	{
		FPerkData* Perk3Data = DataTable.FindRow<FPerkData>(Perk3Name, "");
		if (Perk3Data)
		{
			TSubclassOf<UPerkInstance> Perk3Class = Perk3Data->PerkClass;
			if (Perk3Class)
			{
				UPerkInstance* Perk3Instance = NewObject<UPerkInstance>(this, Perk3Class);
				Perk3Instance->OnInitialized();
			}
		}
	}
	if (Perk4Name != NAME_None)
	{
		FPerkData* Perk4Data = DataTable.FindRow<FPerkData>(Perk4Name, "");
		if (Perk4Data)
		{
			TSubclassOf<UPerkInstance> Perk4Class = Perk4Data->PerkClass;
			if (Perk4Class)
			{
				UPerkInstance* Perk4Instance = NewObject<UPerkInstance>(this, Perk4Class);
				Perk4Instance->OnInitialized();
			}
		}
	}
}

void ADBDCharacter::OnRep_Perk1()
{
}

void ADBDCharacter::OnRep_Perk2()
{
}

void ADBDCharacter::OnRep_Perk3()
{
}

void ADBDCharacter::OnRep_Perk4()
{
}

void ADBDCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(ADBDCharacter, Perk1, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ADBDCharacter, Perk2, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ADBDCharacter, Perk3, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ADBDCharacter, Perk4, COND_None, REPNOTIFY_Always);
}

