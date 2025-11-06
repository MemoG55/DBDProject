// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/Lobby/LobbyLoadOutList.h"

#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "Shared/Controller/LobbyPlayerController.h"
#include "Shared/DataAsset/DBDDataBase.h"
#include "Shared/GameFramework/DBDGameInstance.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/UI/AddonIcon.h"
#include "Shared/UI/Lobby/LobbyItemIcon.h"
#include "Shared/UI/Lobby/LobbyLoadOutSlot.h"
#include "Shared/UI/Lobby/LobbyLoadOutWindow.h"
#include "Shared/UI/Lobby/LobbyPerkIcon.h"

void ULobbyLoadOutList::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// DataBase Initialized
	if (UDBDGameInstance* GI = GetGameInstance<UDBDGameInstance>())
	{
		if (GI->DBDDB)
		{
			SurvivorAddOnData = GI->DBDDB->ItemAddonDB.Get();
			SurvivorItemData = GI->DBDDB->SurvivorItemDB.Get();
			SurvivorPerkData = GI->DBDDB->SurvivorPerkDB.Get();
			KillerPerkData = GI->DBDDB->KillerPerkDB.Get();
		}
	}
}

void ULobbyLoadOutList::BindingPlayerState()
{
}

void ULobbyLoadOutList::BindingPlayerController()
{
	if (ALobbyPlayerController* PC = GetOwningPlayer<ALobbyPlayerController>())
	{
		if (LoadOutListContainer)
		{
			for (UWidget* ChildWidget : LoadOutListContainer->GetAllChildren())
			{
				if (ULobbyLoadOutSlot* LoadOutSlot = Cast<ULobbyLoadOutSlot>(ChildWidget))
				{
					LoadOutSlot->OnLoadOutSlotClicked.AddDynamic(PC, &ALobbyPlayerController::SetLoadOut);
					LoadOutSlot->OnLobbyLoadOutPerkClicked.AddDynamic(PC, &ALobbyPlayerController::SetLoadOutPerk);
					LoadOutSlot->OnLobbyLoadOutItemClicked.AddDynamic(PC, &ALobbyPlayerController::SetLoadOutItem);
					LoadOutSlot->OnLobbyLoadOutAddOnClicked.AddDynamic(PC, &ALobbyPlayerController::SetLoadOutAddOn);
				}
			}
		}
	}
}

void ULobbyLoadOutList::HandleLoadOutList(ADBDPlayerState* PlayerState, ELobbyLoadOutSlotType Type)
{
	TObjectPtr<UDataTable> LoadOutDataTable = nullptr;
	switch (Type)
	{
		case ELobbyLoadOutSlotType::Perk:
			if (PlayerState)
			{
				LoadOutDataTable = PlayerState->GetPlayerRole() == EPlayerRole::Killer ? KillerPerkData : SurvivorPerkData;
			}
			break;
		case ELobbyLoadOutSlotType::Item:
			LoadOutDataTable = SurvivorItemData;
			break;
		case ELobbyLoadOutSlotType::AddOn:
			LoadOutDataTable = SurvivorAddOnData;
			break;
			default:
			break;
	}
	if (LoadOutDataTable == SurvivorAddOnData && PlayerState->SurvivorLoadout.ItemInfo.Item != FName(TEXT("Toolbox")))
	{
		return;
	}
		

	if (LoadOutDataTable && LoadOutSlotClass)
	{
		CurrentListType = Type;
		if (LoadOutListContainer)
		{
			LoadOutListContainer->ClearChildren();
		}
		TArray<FName> RowNames;
		UDataTableFunctionLibrary::GetDataTableRowNames(LoadOutDataTable, RowNames);
		int CurrentRow = 0, CurrentColumn = 0;
		for (FName RowName : RowNames)
		{
			ULobbyLoadOutSlot* LoadOutSlot = CreateWidget<ULobbyLoadOutSlot>(GetOwningPlayer(), LoadOutSlotClass);
			LoadOutSlot->SetSlotType(Type);
			LoadOutSlot->DataRowName = RowName;
			LoadOutSlot->SetDesiredSizeInViewport(FVector2D(1.5f, 1.5f));
			switch (Type)
			{
				case ELobbyLoadOutSlotType::Perk:
					if (FPerkData* Data = LoadOutDataTable->FindRow<FPerkData>(RowName, TEXT("LoadOutList : LoadDataFromPerkTable")))
					{
						if (PerkSlotClass)
						{
							LoadOutSlot->SetData(*Data);
							LoadOutSlot->PerkData = Data;
						}
					}
					break;
				case ELobbyLoadOutSlotType::Item:
					if (FItemData* Data = LoadOutDataTable->FindRow<FItemData>(RowName, TEXT("LobbyHUD : LoadDataFromItemTable")))
					{
						if (ItemSlotClass)
						{
							LoadOutSlot->SetData(*Data);
							LoadOutSlot->ItemData = Data;
						}
					}
					break;
				case ELobbyLoadOutSlotType::AddOn:
					if (FItemAddonData* Data = LoadOutDataTable->FindRow<FItemAddonData>(RowName, TEXT("LobbyHUD : LoadDataFromAddonTable")))
					{
						if (AddOnSlotClass)
						{
							LoadOutSlot->SetData(*Data);
							LoadOutSlot->ItemAddonData = Data;
							
						}
					}
					break;
				default:
				break;
			}
			
			
			
			if (LoadOutListContainer)
			{
				LoadOutListContainer->AddChildToGrid(LoadOutSlot, CurrentRow, CurrentColumn);
			}
			if (CurrentRow < Row)
			{
				CurrentColumn++;
				if (CurrentColumn >= Column)
				{
					CurrentRow++;
					CurrentColumn = 0;
				}
			}
		}
	}
}

ELobbyLoadOutSlotType ULobbyLoadOutList::GetCurrentListType()
{
	return CurrentListType;
}

void ULobbyLoadOutList::OnAddOnLoaded()
{
	if (UDBDGameInstance* GI = GetGameInstance<UDBDGameInstance>())
	{
		if (GI->DBDDB)
		{
			if (GI->DBDDB->ItemAddonDB.IsValid())
			{
				SurvivorAddOnData = GI->DBDDB->ItemAddonDB.Get();
			}
		}
	}
}

void ULobbyLoadOutList::OnItemLoaded()
{
	if (UDBDGameInstance* GI = GetGameInstance<UDBDGameInstance>())
	{
		if (GI->DBDDB)
		{
			if (GI->DBDDB->SurvivorItemDB.IsValid())
			{
				SurvivorItemData = GI->DBDDB->SurvivorItemDB.Get();
			}
		}
	}
}

void ULobbyLoadOutList::OnKillerPerkLoaded()
{
	if (UDBDGameInstance* GI = GetGameInstance<UDBDGameInstance>())
	{
		if (GI->DBDDB)
		{
			if (GI->DBDDB->KillerPerkDB.IsValid())
			{
				KillerPerkData = GI->DBDDB->KillerPerkDB.Get();
			}
		}
	}
}

void ULobbyLoadOutList::OnSurvivorPerkLoaded()
{
	if (UDBDGameInstance* GI = GetGameInstance<UDBDGameInstance>())
	{
		if (GI->DBDDB)
		{
			if (GI->DBDDB->SurvivorPerkDB.IsValid())
			{
				SurvivorPerkData = GI->DBDDB->SurvivorPerkDB.Get();
			}
		}
	}
}



