// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/Lobby/LobbyLoadOutWindow.h"

#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Shared/DataAsset/DBDDataBase.h"
#include "Shared/GameFramework/DBDGameInstance.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/UI/Lobby/LobbyLoadOutList.h"
#include "Shared/UI/Lobby/LobbyLoadOutSlot.h"

void ULobbyLoadOutWindow::NativeConstruct()
{
	Super::NativeConstruct();

	BindingSelf();
}

FReply ULobbyLoadOutWindow::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void ULobbyLoadOutWindow::HandleLoadOutWindow(ELobbyLoadOutSlotType SlotType)
{
	if (ADBDPlayerState* PS = GetOwningPlayerState<ADBDPlayerState>())
	{
		if (LoadOutList)
		{
			LoadOutList->HandleLoadOutList(PS, SlotType);
			LoadOutList->BindingPlayerController();
		}
	}
}

void ULobbyLoadOutWindow::UpdateLoadOutWindow()
{
	UDBDGameInstance* GI = GetWorld()->GetGameInstance<UDBDGameInstance>();
	if (!GI) return;
	if (ADBDPlayerState* PS = GetOwningPlayerState<ADBDPlayerState>())
	{
		if (PerkSlotList)
		{
			TArray<ULobbyLoadOutSlot*> Slots;
			for (UWidget* Child : PerkSlotList->GetAllChildren())
			{
				if (ULobbyLoadOutSlot* ChildSlot = Cast<ULobbyLoadOutSlot>(Child))
				{
					Slots.Add(ChildSlot);
				}
			}
			TArray<FName> RowNames;

			if (PS->GetPlayerRole() == EPlayerRole::Killer)
			{
				RowNames = PS->KillerLoadout.Perks;
				
				for (int32 i = 0; i < Slots.Num(); i++)
				{
					if (!RowNames.IsValidIndex(i)) continue;
					
					if (FPerkData* Data = GI->DBDDB->KillerPerkDB->FindRow<FPerkData>(RowNames[i], TEXT("LoadOutWindow : LoadDataFromPerkTable")))
					{
						Slots[i]->SetData(*Data);
					}
					else
					{
						Slots[i]->SetData(FPerkData());
					}
				}
			}
			else
			{
				RowNames = PS->SurvivorLoadout.Perks;
				for (int32 i = 0; i < Slots.Num(); i++)
				{
					if (!RowNames.IsValidIndex(i)) continue;
					
					if (FPerkData* Data = GI->DBDDB->SurvivorPerkDB->FindRow<FPerkData>(RowNames[i], TEXT("LoadOutWindow : LoadDataFromPerkTable")))
					{
						Slots[i]->SetData(*Data);
					}
					else
					{
						Slots[i]->SetData(FPerkData());
					}
				}
			}

			
		}
		if (ItemSlotList)
		{
			if (ItemSlotList->GetAllChildren().IsValidIndex(0))
			{
				if (ULobbyLoadOutSlot* ChildSlot = Cast<ULobbyLoadOutSlot>(ItemSlotList->GetAllChildren()[0]))
				{
					if (FItemData* Data = GI->DBDDB->SurvivorItemDB->FindRow<FItemData>(PS->SurvivorLoadout.ItemInfo.Item, TEXT("LoadOutWindow : LoadDataFromItemTable")))
					{
						ChildSlot->SetData(*Data);
					}
					else
					{
						ChildSlot->SetData(FItemData());
					}
				}
				
			}
		}
		if (AddOnSlotList)
		{
			TArray<ULobbyLoadOutSlot*> Slots;
			for (UWidget* Child : AddOnSlotList->GetAllChildren())
			{
				if (ULobbyLoadOutSlot* ChildSlot = Cast<ULobbyLoadOutSlot>(Child))
				{
					Slots.Add(ChildSlot);
				}
			}
			TArray<FName*> RowNames;
			{
				RowNames.Add(&PS->SurvivorLoadout.ItemInfo.Addon1);
				RowNames.Add(&PS->SurvivorLoadout.ItemInfo.Addon2);
			}

			for (int32 i = 0; i < Slots.Num(); i++)
			{
				if (FItemAddonData* Data = GI->DBDDB->ItemAddonDB->FindRow<FItemAddonData>(*RowNames[i], TEXT("LoadOutWindow : LoadDataFromAddOnTable")))
				{
					Slots[i]->SetData(*Data);
				}
				else
				{
					Slots[i]->SetData(FItemAddonData());
				}
			}
		}
	}
}

void ULobbyLoadOutWindow::BindingGameState()
{
}

void ULobbyLoadOutWindow::BindingPlayerState(ADBDPlayerState* CurrentPS)
{
	if (ADBDPlayerState* PS = Cast<ADBDPlayerState>(CurrentPS))
	{
		PS->OnPlayerStateUpdatedToSelf.AddDynamic(this, &ThisClass::UpdateLoadOutWindow);
		PS->OnPlayerRoleUpdatedToSelf.AddDynamic(this, &ThisClass::HandleKillerVisibility);
	}
}

void ULobbyLoadOutWindow::BindingPlayerController()
{
}

void ULobbyLoadOutWindow::BindingSelf()
{
	if (PerkSlotList)
	{
		for (UWidget* ChildrenWidget : PerkSlotList->GetAllChildren())
		{
			if (ULobbyLoadOutSlot* PerkSlot = Cast<ULobbyLoadOutSlot>(ChildrenWidget))
			{
				PerkSlot->SetSlotType(ELobbyLoadOutSlotType::Perk);
				PerkSlot->OnLoadOutSlotClicked.AddDynamic(this, &ThisClass::HandleLoadOutWindow);
			}
		}
	}

	if (ItemSlotList)
	{
		for (UWidget* ChildrenWidget : ItemSlotList->GetAllChildren())
		{
			if (ULobbyLoadOutSlot* ItemSlot = Cast<ULobbyLoadOutSlot>(ChildrenWidget))
			{
				ItemSlot->SetSlotType(ELobbyLoadOutSlotType::Item);
				ItemSlot->OnLoadOutSlotClicked.AddDynamic(this, &ThisClass::HandleLoadOutWindow);
			}
		}
	}

	if (AddOnSlotList)
	{
		for (UWidget* ChildrenWidget : AddOnSlotList->GetAllChildren())
		{
			if (ULobbyLoadOutSlot* AddOnSlot = Cast<ULobbyLoadOutSlot>(ChildrenWidget))
			{
				AddOnSlot->SetSlotType(ELobbyLoadOutSlotType::AddOn);
				AddOnSlot->OnLoadOutSlotClicked.AddDynamic(this, &ThisClass::HandleLoadOutWindow);
			}
		}
	}

	if (BtnLoadOutListExit)
	{
		BtnLoadOutListExit->OnClicked.AddDynamic(this, &ThisClass::ExitWindow);
	}
}

FName ULobbyLoadOutWindow::FindDataByRowName(ELobbyLoadOutSlotType Type, const FName& RowName)
{
	if (RowName.IsNone()) return NAME_None;
	
	if (UDBDGameInstance* GI = GetOwningPlayer()->GetWorld()->GetGameInstance<UDBDGameInstance>())
	{
		if (GI->DBDDB)
		{
			switch (Type)
			{
			case ELobbyLoadOutSlotType::Perk:
				if (ADBDPlayerState* PS = GetOwningPlayerState<ADBDPlayerState>())
				{
					if (PS->GetPlayerRole() == EPlayerRole::Killer)
					{
						if (FPerkData* Data = GI->DBDDB->KillerPerkDB->FindRow<FPerkData>(RowName, TEXT("LoadOutWindow(FindByRowName) : LoadDataFromPerkTable")))
						{
							return FName(Data->DisplayName.ToString());
						}
					}
					else
					{
						if (FPerkData* Data = GI->DBDDB->SurvivorPerkDB->FindRow<FPerkData>(RowName, TEXT("LoadOutWindow(FindByRowName) : LoadDataFromPerkTable")))
						{
							return FName(Data->DisplayName.ToString());
						}
					}
				}
				
				break;
			case ELobbyLoadOutSlotType::Item:
				if (FItemData* Data = GI->DBDDB->SurvivorItemDB->FindRow<FItemData>(RowName, TEXT("LoadOutWindow(FindByRowName) : LoadDataFromPerkTable")))
				{
					return FName(Data->DisplayName.ToString());
				}
				break;
			case ELobbyLoadOutSlotType::AddOn:
				if (FItemAddonData* Data = GI->DBDDB->ItemAddonDB->FindRow<FItemAddonData>(RowName, TEXT("LoadOutWindow(FindByRowName) : LoadDataFromPerkTable")))
				{
					return FName(Data->DisplayName.ToString());
				}
				break;
			default:
				return NAME_None;
				break;
			}
			
		}
	}
	return NAME_None;
}

void ULobbyLoadOutWindow::ExitWindow()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void ULobbyLoadOutWindow::HandleKillerVisibility()
{
	if (ADBDPlayerState* PS = GetOwningPlayerState<ADBDPlayerState>())
	{
		if (ItemContainer)
		{
			ItemContainer->SetVisibility(PS->GetPlayerRole() == EPlayerRole::Killer ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
		}
		if (ItemSlotList)
		{
			ItemSlotList->SetVisibility(PS->GetPlayerRole() == EPlayerRole::Killer ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
		}
		if (AddOnSlotList)
		{
			AddOnSlotList->SetVisibility(PS->GetPlayerRole() == EPlayerRole::Killer ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
		}

		UpdateLoadOutWindow();
		HandleLoadOutWindow(ELobbyLoadOutSlotType::Perk);
	}
}
