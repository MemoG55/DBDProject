// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/Lobby/LobbyHUD.h"

#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Shared/Controller/LobbyPlayerController.h"
#include "Shared/GameFramework/DBDGameInstance.h"
#include "Shared/GameFramework/Lobby/LobbyGameState.h"
#include "Shared/GameFramework/Lobby/LobbyPlayerState.h"
#include "Shared/UI/Lobby/LobbyLoadOutWindow.h"
#include "Shared/UI/Lobby/LobbyPlayerSlot.h"

void ULobbyHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (UDBDGameInstance* DBDGI = Cast<UDBDGameInstance>(GetGameInstance()))
	{
		if (DBDGI->DBDDB)
		{
			DBDDataBase = DBDGI->DBDDB;
		}
	}

	// Initialize PlayerSlot
	if (PlayerSlotContainer)
	{
		SurvivorPlayerSlots.Empty();

		for (int32 i = 0; i < PlayerSlotContainer->GetChildrenCount(); i++)
		{
			if (ULobbyPlayerSlot* SurvivorPlayerSlot = Cast<ULobbyPlayerSlot>(PlayerSlotContainer->GetChildAt(i)))
			{
				SurvivorPlayerSlot->SetPlayerRole(EPlayerRole::Survivor);
				SurvivorPlayerSlots.Add(SurvivorPlayerSlot);
			}
		}
	}

	if (KillerPlayerSlot)
	{
		KillerPlayerSlot->SetPlayerRole(EPlayerRole::Killer);
	}

	if (LoadOutWindow)
	{
		LoadOutWindow->SetVisibility(ESlateVisibility::Hidden);
	}

	BindingSelf();
	BindingGameState();
}

void ULobbyHUD::NativeDestruct()
{
	if (ALobbyPlayerController* PC = Cast<ALobbyPlayerController>(GetOwningPlayer()))
	{
		if (Button_HandleReady)
		{
			Button_HandleReady->OnClicked.RemoveDynamic(PC, &ALobbyPlayerController::SetReady);
		}
		if (Button_HandleRole)
		{
			Button_HandleRole->OnClicked.RemoveDynamic(PC, &ALobbyPlayerController::SetRole);
		}
		if (Button_HandleLoadout)
		{
			Button_HandleLoadout->OnClicked.RemoveDynamic(this, &ThisClass::HandleLoadOut);
		}
		if (ALobbyGameState* GS = PC->GetWorld()->GetGameState<ALobbyGameState>())
		{
			//GS->OnPlayerStatesUpdated.RemoveDynamic(this, &ThisClass::OnRep_OnPlayerStateUpdatedFromGameState);
		}
	}
	Super::NativeDestruct();
}

void ULobbyHUD::BindingGameState()
{
	if (!GetWorld()) return;
	
	if (ALobbyGameState* GS = GetWorld()->GetGameState<ALobbyGameState>())
	{
		GS->OnPlayerStatesUpdated.AddDynamic(this, &ThisClass::OnRep_OnPlayerStateUpdatedFromGameState);
		GS->OnPlayerStateAdded.AddDynamic(this, &ThisClass::BindingOtherPlayerState);
			
		OnRep_OnPlayerStateUpdatedFromGameState();
	}
}

void ULobbyHUD::BindingOtherPlayerState(ADBDPlayerState* OtherPS)
{
	if (IsValid(OtherPS) && OtherPS != GetOwningPlayerState<ADBDPlayerState>())
	{
		OtherPS->OnPlayerStateUpdatedToOther.AddDynamic(this, &ThisClass::OnRep_OnPlayerStateUpdatedFromOther);
		OtherPS->OnPlayerRoleUpdatedToOther.AddDynamic(this, &ThisClass::OnRep_OnPlayerStateUpdatedFromOther);
	}
}

void ULobbyHUD::BindingPlayerState(ADBDPlayerState* CurrentPS)
{
	if (ALobbyPlayerState* PS = Cast<ALobbyPlayerState>(CurrentPS))
	{
		PS->OnReadyStateUpdatedToSelf.AddDynamic(this, &ThisClass::OnRep_OnReadyStateUpdatedFromSelf);
		PS->OnPlayerStateUpdatedToSelf.AddDynamic(this, &ThisClass::OnRep_OnPlayerStateUpdatedFromSelf);
	}
}

void ULobbyHUD::BindingPlayerController()
{
	if (ALobbyPlayerController* PC = Cast<ALobbyPlayerController>(GetOwningPlayer()))
	{
		if (Button_HandleReady)
		{
			Button_HandleReady->OnClicked.AddDynamic(PC, &ALobbyPlayerController::SetReady);
		}
		if (Button_HandleRole)
		{
			Button_HandleRole->OnClicked.AddDynamic(PC, &ALobbyPlayerController::SetRole);
		}
	}
}

void ULobbyHUD::BindingSelf()
{
	if (Button_HandleLoadout)
	{
		Button_HandleLoadout->OnClicked.AddDynamic(this, &ThisClass::HandleLoadOut);
	}
}

void ULobbyHUD::OnRep_OnReadyStateUpdatedFromSelf()
{
	if (ALobbyPlayerState* PS = GetOwningPlayer()->GetPlayerState<ALobbyPlayerState>())
	{
		if (TBReadyState)
		{
			TBReadyState.Get()->SetText(FText::FromString(PS->GetReady() ? "Cancel" : "Ready"));
		}
	}
}

void ULobbyHUD::OnRep_OnPlayerStateUpdatedFromGameState()
{
	// PlayerRole 변경 시 슬롯 갱신(킬러, 생존자 모두) 
	if (ALobbyGameState* GS = GetOwningPlayer()->GetWorld()->GetGameState<ALobbyGameState>())
	{
		for (int32 i = 0; i < SurvivorPlayerSlots.Num(); i++)
		{
			ADBDPlayerState* PS = GS->SurvivorPlayerStates[i];
			SurvivorPlayerSlots[i]->SetPlayerSlot(PS);
		}
		
		if (KillerPlayerSlot)
		{
			KillerPlayerSlot->SetPlayerSlot(GS->KillerPlayerState);
		}
	}

	if (ADBDPlayerState* PS = GetOwningPlayerState<ADBDPlayerState>())
	{
		if (TBRoleState)
		{
			//TBRoleState->SetText(FText::FromString(PS->GetPlayerRole() == EPlayerRole::Killer ? "To Survivor" : "To Killer"));
		}
	}
}

void ULobbyHUD::OnRep_OnPlayerStateUpdatedFromSelf()
{
	HandlePlayerSlot(GetOwningPlayerState<ADBDPlayerState>());
}

void ULobbyHUD::OnRep_OnPlayerStateUpdatedFromOther(ADBDPlayerState* OtherPS)
{
	// 생존자 슬롯 업데이트(캐릭터 변경용도 추후 레디상태 변경도 적용 가능할듯?)
	HandlePlayerSlot(OtherPS);
}

void ULobbyHUD::HandleLoadOut()
{
	if (LoadOutWindow)
	{
		if (LoadOutWindow->IsVisible())
		{
			LoadOutWindow->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			LoadOutWindow->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void ULobbyHUD::HandlePlayerSlot(ADBDPlayerState* PS)
{
	if (ALobbyGameState* GS = GetOwningPlayer()->GetWorld()->GetGameState<ALobbyGameState>())
	{
		int32 FoundIndex = GS->SurvivorPlayerStates.IndexOfByPredicate([PS](ADBDPlayerState* ExistingPS)
		{
			return ExistingPS == PS; 
		});
		if (FoundIndex != INDEX_NONE)
		{
			if (SurvivorPlayerSlots.IsValidIndex(FoundIndex))
			{
				//SurvivorPlayerSlots[FoundIndex]->SetPlayerSlot(PS);
			}
		}
		else
		{
			//KillerPlayerSlot->SetPlayerSlot(GS->KillerPlayerState);
		}
	}
}

ULobbyLoadOutWindow* ULobbyHUD::GetLoadOutWindow()
{
	return LoadOutWindow;
}
