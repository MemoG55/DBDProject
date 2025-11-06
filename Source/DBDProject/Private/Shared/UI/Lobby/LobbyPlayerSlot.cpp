// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/Lobby/LobbyPlayerSlot.h"

#include "Components/ComboBoxString.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "Shared/Controller/DBDPlayerController.h"
#include "Shared/Controller/LobbyPlayerController.h"
#include "Shared/DataAsset/DBDDataBase.h"
#include "Shared/GameFramework/DBDGameInstance.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/GameFramework/Lobby/LobbyPlayerState.h"

void ULobbyPlayerSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// DataBase Initialized
	if (UDBDGameInstance* GI = GetGameInstance<UDBDGameInstance>())
	{
		if (GI->DBDDB)
		{
			CharacterDB = GI->DBDDB->SurvivorCharacterDB.Get();
			InitCharacterMeshSelect();
			// FSoftObjectPath DBPath = GI->DBDDB->SurvivorCharacterDB.ToSoftObjectPath();
			// UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
			// 	DBPath, FStreamableDelegate::CreateUObject(this, &ThisClass::OnCharacterLoaded));
		}
	}

	BindingSelf();
}

void ULobbyPlayerSlot::NativeConstruct()
{
	Super::NativeConstruct();

	
}

void ULobbyPlayerSlot::NativeDestruct()
{
	Super::NativeDestruct();

	if (CBMeshSelect)
	{
		if (ALobbyPlayerController* PC = GetOwningPlayer<ALobbyPlayerController>())
		{
			CBMeshSelect->OnSelectionChanged.RemoveAll(PC);
		}
	}
}

void ULobbyPlayerSlot::BindingGameState()
{
}

void ULobbyPlayerSlot::BindingPlayerState(ADBDPlayerState* PS)
{
	if (OldPS)
	{
		OldPS->OnPlayerStateUpdatedToSelf.RemoveAll(this);
		if (ALobbyPlayerState* LobbyPS = Cast<ALobbyPlayerState>(OldPS))
		{
			LobbyPS->OnReadyStateUpdatedToSelf.RemoveAll(this);
		}
		OldPS = nullptr;
	}
	if (PS)
	{
		OldPS = PS;
		PS->OnPlayerStateUpdatedToSelf.AddDynamic(this, &ThisClass::HandleOwning);
		if (ALobbyPlayerState* LobbyPS = Cast<ALobbyPlayerState>(OldPS))
		{
			LobbyPS->OnReadyStateUpdatedToSelf.AddDynamic(this, &ThisClass::HandleOwning);
		}
	}
}

void ULobbyPlayerSlot::BindingPlayerController()
{
	if (ALobbyPlayerController* PC = GetOwningPlayer<ALobbyPlayerController>())
	{
		
	}
}

void ULobbyPlayerSlot::BindingSelf()
{
	if (CBMeshSelect)
	{
		CBMeshSelect->OnSelectionChanged.AddDynamic(this, &ThisClass::OnChangedMeshSelection);
	}
}

void ULobbyPlayerSlot::OnCharacterLoaded()
{
	if (UDBDGameInstance* GI = GetGameInstance<UDBDGameInstance>())
	{
		if (GI->DBDDB)
		{
			if (GI->DBDDB->SurvivorCharacterDB.IsValid())
			{
				CharacterDB = GI->DBDDB->SurvivorCharacterDB.Get();

				InitCharacterMeshSelect();
			}
		}
	}
}

void ULobbyPlayerSlot::InitCharacterMeshSelect()
{
	
	if (CharacterDB)
	{
		TArray<FName> RowNames;
		UDataTableFunctionLibrary::GetDataTableRowNames(CharacterDB, RowNames);
		CBMeshSelect->ClearOptions();
		
		for (FName RowName : RowNames)
		{
			if (CharacterDB->FindRow<FSurvivorCharacterData>(RowName, TEXT("LobbyHUD : LoadDataFromCharacterDB")))
			{
				CBMeshSelect->AddOption(RowName.ToString());
			}
		}
	}
}

void ULobbyPlayerSlot::HandleOwning()
{
	HandleMeshSelection(ESlateVisibility::Hidden);
	
	if (OldPS)
	{
		if (ALobbyPlayerState* LobbyPS = Cast<ALobbyPlayerState>(OldPS))
		{
			if (LobbyPS->GetReady())
			{
				PlayerImage->SetBrushFromTexture(ReadyImage);	
			}
			else
			{
				PlayerImage->SetBrushFromTexture(OldPS->GetPlayerRole() == EPlayerRole::Killer ? KillerImage : SurvivorImage);
			}
		}
		
		SetPlayerName(OldPS->GetPlayerName());
		if (OldPS->GetPlayerRole() == EPlayerRole::Survivor)
		{
			SetPlayerMesh(OldPS->SurvivorLoadout.Character.ToString());
			
			if (OldPS->GetPlayerController())
			{
				if (OldPS->GetPlayerController()->IsLocalController())
				{
					HandleMeshSelection(ESlateVisibility::Visible);
				}
			}
		}
		else if (OldPS->GetPlayerRole() == EPlayerRole::Killer)
		{
			MeshImage->SetBrushFromTexture(MeshKillerImage);
		}
	}
	else
	{
		SetPlayerName("");
		MeshImage->SetBrushFromTexture(MeshNoneImage);
	}
}

void ULobbyPlayerSlot::HandleByOther()
{
}


void ULobbyPlayerSlot::HandleMeshSelection(ESlateVisibility bVisiblity)
{
	if (CBMeshSelect)
	{
		CBMeshSelect->SetVisibility(bVisiblity);
	}
}

void ULobbyPlayerSlot::SetPlayerSlot(ADBDPlayerState* PS)
{
	BindingPlayerState(PS);
	HandleOwning();
	//
	// HandleMeshSelection(ESlateVisibility::Hidden);
	// if (IsValid(PS))
	// {
	// 	FString PlayerName = PS->GetPlayerName();
	// 	SetPlayerName(PlayerName);
	//
	// 	if (PS->GetPlayerRole() == EPlayerRole::Survivor)
	// 	{
	// 		SetPlayerMesh(PS->SurvivorLoadout.Character.ToString());
	// 		
	// 		if (PS->GetPlayerController())
	// 		{
	// 			if (PS->GetPlayerController()->IsLocalController())
	// 			{
	// 				HandleMeshSelection(ESlateVisibility::Visible);
	// 			}
	// 		}
	// 	}
	// 	else if (PS->GetPlayerRole() == EPlayerRole::Killer)
	// 	{
	// 		//MeshImage->SetBrushFromTexture(MeshKillerImage);
	// 	}
	// }
	// else
	// {
	// 	SetPlayerName("");
	// 	SetPlayerMesh("");
	// }
}

void ULobbyPlayerSlot::SetPlayerRole(const EPlayerRole& PlayerRole)
{
	if (TBPlayerRole)
	{
		TBPlayerRole->SetText(UEnum::GetDisplayValueAsText(PlayerRole));
		
	}
	if (PlayerImage)
	{
		PlayerImage->SetBrushFromTexture(PlayerRole == EPlayerRole::Killer ? KillerImage : SurvivorImage);
	}
	if (PlayerRole == EPlayerRole::Killer)
	{
		//MeshImage->SetBrushFromTexture(MeshKillerImage);
	}
}

void ULobbyPlayerSlot::SetPlayerName(const FString& PlayerName)
{
	if (TBPlayerName)
	{
		TBPlayerName->SetText(FText::FromString(PlayerName));
		if (GetOwningPlayerState())
		{
			if (GetOwningPlayerState()->GetPlayerNameCustom() == PlayerName)
			{
				TBPlayerName->SetColorAndOpacity(FColor::Yellow);
			}
			else
			{
				TBPlayerName->SetColorAndOpacity(FColor::White);
			}
		}
	}
}

void ULobbyPlayerSlot::SetPlayerMesh(const FString& PlayerMesh)
{
	if (CharacterDB)
	{
		if (PlayerMesh.IsEmpty()) return;
		
		if (FSurvivorCharacterData* CharacterData = CharacterDB->FindRow<FSurvivorCharacterData>(FName(PlayerMesh), TEXT("LobbyHUD : LoadDataFromCharacterDB")))
		{
			if (MeshImage)
			{
				MeshImage->SetBrushFromTexture(CharacterData->CharacterPortrait.Get());
				return;
			}
		}
	}
	if (MeshImage)
	{
		MeshImage->SetBrushFromTexture(MeshNoneImage);
	}
}

void ULobbyPlayerSlot::OnChangedMeshSelection(FString SelectedItem, ESelectInfo::Type SelectType)
{
	if (ALobbyPlayerController* PC = GetOwningPlayer<ALobbyPlayerController>())
	{
		PC->SetCharacterMesh(SelectedItem, SelectType);
	}
}
