// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/GameFramework/Lobby/LobbyGameMode.h"

#include <string>

#include "GameFramework/GameStateBase.h"
#include "Net/Core/PushModel/PushModel.h"
#include "Shared/DBDEnum.h"
#include "Shared/GameFramework/DBDGameInstance.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/GameFramework/Lobby/LobbyGameState.h"
#include "Shared/GameFramework/Lobby/LobbyPlayerState.h"


ALobbyGameMode::ALobbyGameMode()
{
	bUseSeamlessTravel = true;
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	if (!GameState) return;

	if (IsKillerExists() && IsSurvivorFull())
	{
		Logout(NewPlayer);
		return;
	}

	ALobbyGameState* GS = Cast<ALobbyGameState>(GetWorld()->GetGameState());
	if (!GS) return;
	
	if (ALobbyPlayerState* PS = NewPlayer->GetPlayerState<ALobbyPlayerState>())
	{
		// 1. AddDelegate (CurrentPS -> OtherPS)
		for (APlayerState* ExistingPS : GS->PlayerArray)
		{
			if (ALobbyPlayerState* OtherPS = Cast<ALobbyPlayerState>(ExistingPS))
			{
				if (OtherPS != PS)
				{
					OtherPS->OnPlayerStateUpdatedToOther.AddDynamic(PS, &ALobbyPlayerState::OnRep_OnPlayerStateUpdatedFromOther);
					OtherPS->OnPlayerRoleUpdatedToOther.AddDynamic(PS, &ALobbyPlayerState::OnRep_OnPlayerStateUpdatedFromOther);

					PS->OnRep_OnPlayerStateUpdatedFromOther(OtherPS);
				}
			}
		}
		// 2. AddDelegate (OtherPS -> CurrentPS)
		for (APlayerState* ExistingPS : GS->PlayerArray)
		{
			if (ALobbyPlayerState* OtherPS = Cast<ALobbyPlayerState>(ExistingPS))
			{
				if (OtherPS != PS)
				{
					PS->OnPlayerStateUpdatedToOther.AddDynamic(OtherPS, &ALobbyPlayerState::OnRep_OnPlayerStateUpdatedFromOther);
					PS->OnPlayerRoleUpdatedToOther.AddDynamic(OtherPS, &ALobbyPlayerState::OnRep_OnPlayerStateUpdatedFromOther);

					OtherPS->OnRep_OnPlayerStateUpdatedFromOther(PS);
				}
			}
		}

		// 3. AddDelegate (CurrentPS -> GameState)
		GS->OnPlayerStateAdded.AddDynamic(PS, &ALobbyPlayerState::OnRep_OnPlayerStateAddedToSelf);
		
		
		// SetPlayerRole
		// 첫번째로 들어오거나, 킬러 자리가 비었을 경우 들어오게 되면 킬러로 배정
		if (GameState->PlayerArray.Num() == 1 || !IsKillerExists())
		{
			InitializePlayerRole(PS, EPlayerRole::Killer);
		}
		// 이외의 경우 모두 생존자로 지정
		else
		{
			InitializePlayerRole(PS, EPlayerRole::Survivor);
		}
		FString PlayerNameString = FString::Printf(TEXT("Player%d"), GameState->PlayerArray.Num());
		PS->SetPlayerName(PlayerNameString);
	}
	
}

void ALobbyGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
}

void ALobbyGameMode::GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList)
{
	Super::GetSeamlessTravelActorList(bToTransition, ActorList);
}

void ALobbyGameMode::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();
}

void ALobbyGameMode::HandlePlayerRole(ADBDPlayerState* CurrentPlayerState, EPlayerRole NewRole)
{
	if (!IsValid(CurrentPlayerState)) return;

	if (ALobbyPlayerState* PS = Cast<ALobbyPlayerState>(CurrentPlayerState))
	{
		if (PS->GetReady())
		{
			// Ready한 상태에서는 못바꿈
			return;
		}
	}

	if (ALobbyGameState* GS = Cast<ALobbyGameState>(GetWorld()->GetGameState()))
	{
		// 살인마 -> 생존자 변경
		if (NewRole == EPlayerRole::Survivor)
		{
			if (IsSurvivorFull()) return;
			
			int32 FoundIndex = GS->SurvivorPlayerStates.IndexOfByPredicate([](ADBDPlayerState* OtherPS)
			{
				// 포인터가 가리키는 FName의 값(문자열)을 비교
				return !IsValid(OtherPS); 
			});
			if (FoundIndex != INDEX_NONE)
			{
				if (GS->SurvivorPlayerStates.IsValidIndex(FoundIndex))
				{
					GS->SurvivorPlayerStates[FoundIndex] = CurrentPlayerState;
					
					GS->KillerPlayerState = nullptr;

					CurrentPlayerState->SetPlayerRole(NewRole);
				}
			}
		}
		// 생존자 -> 살인마 변경
		else
		{
			if (IsKillerExists()) return;
			
			int32 FoundIndex = GS->SurvivorPlayerStates.IndexOfByPredicate([CurrentPlayerState](ADBDPlayerState* OtherPS)
			{
				// 포인터가 가리키는 FName의 값(문자열)을 비교
				return IsValid(CurrentPlayerState) && OtherPS == CurrentPlayerState; 
			});
			if (FoundIndex != INDEX_NONE)
			{
				if (GS->SurvivorPlayerStates.IsValidIndex(FoundIndex))
				{
					GS->SurvivorPlayerStates[FoundIndex] = nullptr;
					
					GS->KillerPlayerState = CurrentPlayerState;
					
					CurrentPlayerState->SetPlayerRole(NewRole);
				}
			}
		}
		/* MMJ :
		 * 푸시 모델 (Push Model): 개발자가 MARK_PROPERTY_DIRTY를 호출하여 **"이 변수가 변경되었으니 복제해야 한다"**고 명시적으로 알려줄 때만 복제 처리가 시작되어,
		 * 네트워크 성능을 최적화하는 데 사용됩니다. 이 기능을 사용하려면 NetCore 모듈이 반드시 링크되어야 합니다.
		 */
		MARK_PROPERTY_DIRTY_FROM_NAME(ALobbyGameState, KillerPlayerState, GS);
		MARK_PROPERTY_DIRTY_FROM_NAME(ALobbyGameState, SurvivorPlayerStates, GS);
	}
}

void ALobbyGameMode::InitializePlayerRole(ADBDPlayerState* CurrentPlayerState, EPlayerRole NewRole)
{
	if (ALobbyGameState* GS = Cast<ALobbyGameState>(GetWorld()->GetGameState()))
	{
		if (NewRole == EPlayerRole::Killer)
		{
			GS->KillerPlayerState = CurrentPlayerState;
			CurrentPlayerState->SetPlayerRole(NewRole);
		}
		else
		{
			int32 FoundIndex = GS->SurvivorPlayerStates.IndexOfByPredicate([](ADBDPlayerState* OtherPS)
			{
				return !IsValid(OtherPS); 
			});
			if (FoundIndex != INDEX_NONE)
			{
				if (GS->SurvivorPlayerStates.IsValidIndex(FoundIndex))
				{
					GS->SurvivorPlayerStates[FoundIndex] = CurrentPlayerState;
					CurrentPlayerState->SetPlayerRole(NewRole);
				}
			}
		}
	}
}

void ALobbyGameMode::OnAllPlayerIsReady()
{
	bool bIsReady = true;
	for (APlayerState* PS : GameState->PlayerArray)
	{
		if (ALobbyPlayerState* LobbyPS = Cast<ALobbyPlayerState>(PS))
		{
			if (bIsReady != LobbyPS->GetReady())
			{
				bIsReady = LobbyPS->GetReady();
				break;
			}
		}
	}

	if (ALobbyGameState* GS = GetGameState<ALobbyGameState>())
	{
		if (!GS->KillerPlayerState)
		{
			bIsReady = false;
		}
	}
	
	if (bIsReady && IsValid(GetWorld()))
	{
		// 게임으로 이동
		GetWorld()->ServerTravel("/Game/_BP/Shared/Level/InGameLevel?listen", true, false);
	}
}

void ALobbyGameMode::HandlePlayerReadyState(ADBDPlayerState* CurrentPlayerState, bool bIsReady)
{
	if (!IsValid(CurrentPlayerState)) return;
	
	if (ALobbyPlayerState* PS = Cast<ALobbyPlayerState>(CurrentPlayerState))
	{
		PS->SetReady(bIsReady);
		
		OnAllPlayerIsReady();
	}
}

void ALobbyGameMode::HandleLoadOutPerk(ADBDPlayerState* CurrentPlayerState, const FName& DataRowName)
{
	if (!IsValid(CurrentPlayerState)) return;
	if (!DataRowName.IsValid() || DataRowName.IsNone()) return;

	FName DataRowNameText = FName(DataRowName.ToString());
	if (ADBDPlayerState* PS = Cast<ADBDPlayerState>(CurrentPlayerState))
	{
		TArray<FName>* Datas =  PS->GetPlayerRole() == EPlayerRole::Killer ? &PS->KillerLoadout.Perks : &PS->SurvivorLoadout.Perks;

		// 1. If Data Is Exists Remove Data;
		int32 FoundIndex = Datas->IndexOfByPredicate([DataRowNameText](FName TargetData)
			{
				return TargetData.IsValid() && TargetData == DataRowNameText; 
			});
		if (FoundIndex != INDEX_NONE)
		{
			(*Datas)[FoundIndex] = NAME_None;
			return;
		}

		// 2. If Data Is Not Exists Add Data;
		for (int32 i = 0; i < Datas->Num(); i++)
		{
			if ((*Datas)[i] == NAME_None || (*Datas)[i].IsNone())
			{
				(*Datas)[i] = DataRowNameText;
				break;
			}
		}

		if (PS->GetPlayerRole() == EPlayerRole::Killer)
		{
			MARK_PROPERTY_DIRTY_FROM_NAME(ADBDPlayerState, KillerLoadout, PS);
		}
		else
		{
			MARK_PROPERTY_DIRTY_FROM_NAME(ADBDPlayerState, SurvivorLoadout, PS);
		}
	}
}

void ALobbyGameMode::HandleLoadOutItem(ADBDPlayerState* CurrentPlayerState, const FName& DataRowName)
{
	if (!IsValid(CurrentPlayerState)) return;
	if (!DataRowName.IsValid() || DataRowName.IsNone()) return;
	
	
	if (ALobbyPlayerState* PS = Cast<ALobbyPlayerState>(CurrentPlayerState))
	{
		if (PS->SurvivorLoadout.ItemInfo.Item.IsNone() && DataRowName.IsValid())
		{
			PS->SurvivorLoadout.ItemInfo.Item = FName(DataRowName.ToString());
			MARK_PROPERTY_DIRTY_FROM_NAME(ADBDPlayerState, SurvivorLoadout, PS);
			return;
		}
		
		if (PS->SurvivorLoadout.ItemInfo.Item.IsValid() && PS->SurvivorLoadout.ItemInfo.Item == DataRowName)
		{
			PS->SurvivorLoadout.ItemInfo.Item = NAME_None;
			PS->SurvivorLoadout.ItemInfo.Addon1 = NAME_None;
			PS->SurvivorLoadout.ItemInfo.Addon2 = NAME_None;
			MARK_PROPERTY_DIRTY_FROM_NAME(ADBDPlayerState, SurvivorLoadout, PS);
			return;
		}
	}
	
}

void ALobbyGameMode::HandleLoadOutAddOn(ADBDPlayerState* CurrentPlayerState, const FName& DataRowName)
{
	if (!IsValid(CurrentPlayerState)) return;
	if (!DataRowName.IsValid() || DataRowName.IsNone()) return;
	FName DataRowNameText = FName(DataRowName.ToString());
	if (ALobbyPlayerState* PS = Cast<ALobbyPlayerState>(CurrentPlayerState))
	{
		TArray<FName*> AddOns;
		AddOns.Add(&PS->SurvivorLoadout.ItemInfo.Addon1);
		AddOns.Add(&PS->SurvivorLoadout.ItemInfo.Addon2);

		int32 FoundIndex = AddOns.IndexOfByPredicate([DataRowNameText](FName* AddOnPtr)
			{
				// 포인터가 가리키는 FName의 값(문자열)을 비교
				return AddOnPtr->IsValid() && *AddOnPtr == DataRowNameText; 
			});
		if (FoundIndex != INDEX_NONE)
		{
			*AddOns[FoundIndex] = NAME_None;
			MARK_PROPERTY_DIRTY_FROM_NAME(ADBDPlayerState, SurvivorLoadout, PS);
			return;
		}
		
		for (FName* AddOn : AddOns)
		{
			if (AddOn->IsNone())
			{
				*AddOn = DataRowNameText;
				break;
			}
		}
		MARK_PROPERTY_DIRTY_FROM_NAME(ADBDPlayerState, SurvivorLoadout, PS);
	}
}

void ALobbyGameMode::HandleCharacterMesh(ADBDPlayerState* CurrentPlayerState, const FName& SourceData)
{
	if (!IsValid(CurrentPlayerState)) return;
	if (!SourceData.IsValid() || SourceData.IsNone()) return;

	CurrentPlayerState->SurvivorLoadout.Character = SourceData;
	MARK_PROPERTY_DIRTY_FROM_NAME(ADBDPlayerState, SurvivorLoadout, CurrentPlayerState);
}

bool ALobbyGameMode::IsKillerExists()
{
	if (ALobbyGameState* GS = GetGameState<ALobbyGameState>())
	{
		// 살인마가 배정된 상태를 반환 (배정됨 = true, 배정되지 않음 = false)
		return IsValid(GS->KillerPlayerState);
	}
	// 오류날 시 
	return false;
}

bool ALobbyGameMode::IsSurvivorFull()
{
	if (ALobbyGameState* GS = GetGameState<ALobbyGameState>())
	{
		int32 FoundIndex = GS->SurvivorPlayerStates.IndexOfByPredicate([](ADBDPlayerState* OtherPS)
		{
			// Find Empty Place
			return !IsValid(OtherPS); 
		});
		if (FoundIndex == INDEX_NONE)
		{
			// If That is not Empty Array return Survivor is Full
			return true;
		}
	}
	return false;
}
