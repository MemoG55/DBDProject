// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Character/DBDCharacter.h"
#include "AbilitySystemInterface.h"
#include "Components/CapsuleComponent.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDEnum.h"
#include "Shared/Animation/DBDAnimInstance.h"
#include "Shared/DataAsset/DBDDataBase.h"
#include "Shared/GameFramework/DBDGameInstance.h"
#include "Shared/GameFramework/DBDGameMode.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/Perk/PerkInstance.h"

ADBDCharacter::ADBDCharacter()
{
	NetUpdateFrequency = 100.0f;
	//bReplicates = true;
	//bAlwaysRelevant = true;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCharacterMovement()->SetWalkableFloorAngle(55.f);
	GetCharacterMovement()->MaxStepHeight = 55.f;
}

UAbilitySystemComponent* ADBDCharacter::GetAbilitySystemComponent() const
{
	// IAbilitySystemInterface* PSASInterface = Cast<IAbilitySystemInterface>(GetPlayerState());
	// if (PSASInterface)
	// {
	// 	return PSASInterface->GetAbilitySystemComponent();
	// }
	// 자식에서 구현
	return nullptr;
}

void ADBDCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// 자식에서 ASC초기화 이후에 AuthInitPerks() 호출
	// MMJ 수정 NewController가 Nullptr에러 발생해서 캐스팅 수정
	if (APlayerController* const PC = Cast<APlayerController>(NewController))
	{
		if (PC->IsLocalController())
		{
			FInputModeGameOnly InputMode;
			InputMode.SetConsumeCaptureMouseDown(true);
			PC->bShowMouseCursor = false;
			PC->SetInputMode(InputMode);
		}
	}
}

void ADBDCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(true);
		PC->bShowMouseCursor = false;
		PC->SetInputMode(InputMode);
	}
}

void ADBDCharacter::AuthInitPerks()
{
	if (!HasAuthority())
	{
		return;
	}
	ADBDPlayerState* PS = Cast<ADBDPlayerState>(GetPlayerState());
	if (!PS)
	{
		return;
	}
	UDBDGameInstance* GI = Cast<UDBDGameInstance>(GetGameInstance());
	if (!GI || !GI->DBDDB)
	{
		return;
	}
	if (PS->GetPlayerRole() == EPlayerRole::Survivor)
	{
		UDataTable* DT = Cast<UDataTable>(
			UAssetManager::Get().GetStreamableManager().LoadSynchronous(
				GI->DBDDB->SurvivorPerkDB.ToSoftObjectPath()));
		if (DT)
		{
			InitializePerks(*DT, PS->SurvivorLoadout.Perk1, PS->SurvivorLoadout.Perk2,
			                PS->SurvivorLoadout.Perk3, PS->SurvivorLoadout.Perk4);
		};
	}
	else
	{
		UDataTable* DT = Cast<UDataTable>(
			UAssetManager::Get().GetStreamableManager().LoadSynchronous(
				GI->DBDDB->KillerPerkDB.ToSoftObjectPath()));
		if (DT)
		{
			InitializePerks(*DT, PS->KillerLoadout.Perk1, PS->KillerLoadout.Perk2,
			                PS->KillerLoadout.Perk3, PS->KillerLoadout.Perk4);
		};
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
				Perk1 = NewObject<UPerkInstance>(this, Perk1Class);
				Perk1->OnInitialized();
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
				Perk2 = NewObject<UPerkInstance>(this, Perk2Class);
				Perk2->OnInitialized();
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
				Perk3 = NewObject<UPerkInstance>(this, Perk3Class);
				Perk3->OnInitialized();
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
				Perk4 = NewObject<UPerkInstance>(this, Perk4Class);
				Perk4->OnInitialized();
			}
		}
	}
}

void ADBDCharacter::ServerSideInit()
{
	// 자식에서 구현
}

void ADBDCharacter::ClientSideInit()
{
	// 자식에서 구현
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
