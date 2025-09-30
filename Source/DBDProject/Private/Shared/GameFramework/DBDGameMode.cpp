// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/GameFramework/DBDGameMode.h"

#include "Engine/AssetManager.h"
#include "GameFramework/GameStateBase.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "KMJ/Character/KillerCharacter.h"
#include "Shared/GameFramework/DBDGameStateBase.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDEnum.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/DataAsset/DBDDataBase.h"
#include "Shared/GameFramework/DBDGameInstance.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/Subsystem/DBDCharacterObserver.h"
#include "Widgets/SViewport.h"

ADBDGameMode::ADBDGameMode()
{
}

void ADBDGameMode::BeginPlay()
{
	Super::BeginPlay();

	DBDGameState = Cast<ADBDGameStateBase>(GameState);
	if (DBDGameState)
	{
		// MMJ : 탈출구 개방 시 타이머 델리게이트 연결
		DBDGameState->OnEscapeTimerEnd.AddDynamic(this, &ThisClass::EndGameState);
	}
}

void ADBDGameMode::PostLogin(APlayerController* NewPlayer)
{
	if (ADBDPlayerState* PS = NewPlayer->GetPlayerState<ADBDPlayerState>())
	{
		int32 CurrentCount = GameState->PlayerArray.Num();
		if (CurrentCount == 1) // 첫 번째 플레이어
		{
			PS->SetPlayerRole(EPlayerRole::Killer);
			// PS->AuthInitAttributeSet();
		}
		else
		{
			PS->SetPlayerRole(EPlayerRole::Survivor);
			// PS->AuthInitAttributeSet();
		}
	}
	// 역할 지정 후에 HandleStartingNewPlayer() 호출(캐릭터 스폰)
	Super::PostLogin(NewPlayer);
}

void ADBDGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	ADBDPlayerState* PS = NewPlayer->GetPlayerState<ADBDPlayerState>();
	if (!PS)
	{
		return;
	}
	UDBDCharacterObserver* CharacterObserver = GetWorld()->GetSubsystem<UDBDCharacterObserver>();
	if (!CharacterObserver)
	{
		Debug::Print(TEXT("JMS11: CharacterObserver is NULL!"), 11);
		return;
	}
	// 역할 별 캐릭터 스폰 후 Possess(ASC는 캐릭터로 옮김)
	if (PS->GetPlayerRole() == EPlayerRole::Killer)
	{
		APawn* KillerPawn = GetWorld()->SpawnActor<APawn>(KillerCharacterClass,
		                                                  ChoosePlayerStart(NewPlayer)->GetActorTransform());
		if (AKillerCharacter* KillerCharacter = Cast<AKillerCharacter>(KillerPawn))
		{
			CharacterObserver->RegisterKiller(KillerCharacter);
		}
		NewPlayer->Possess(KillerPawn);
	}
	else
	{
		APawn* SurvivorPawn = GetWorld()->SpawnActor<APawn>(SurvivorCharacterClass,
		                                                    ChoosePlayerStart(NewPlayer)->GetActorTransform());
		if (ASurvivorCharacter* SurvivorCharacter = Cast<ASurvivorCharacter>(SurvivorPawn))
		{
			CharacterObserver->RegisterSurvivor(SurvivorCharacter);
		}
		NewPlayer->Possess(SurvivorPawn);
	}

}

void ADBDGameMode::CheckGameCondition()
{
	int32 Alive = 0, Dead = 0, Escape = 0, Total = GameState->PlayerArray.Num();

	if (UDBDCharacterObserver* DBDCObserver = GetWorld()->GetSubsystem<UDBDCharacterObserver>())
	{
		if (DBDCObserver->GetSurvivors().Num() <= 0) return;
		
		for (TObjectPtr<ADBDCharacter> Character : DBDCObserver->GetSurvivors())
		{
			if (UAbilitySystemComponent* ASC = Character.Get()->GetAbilitySystemComponent())
			{
				if (ASC->HasMatchingGameplayTag(DBDGameplayTags::Survivor_Status_Dead)) Dead++;
				else if (ASC->HasMatchingGameplayTag(DBDGameplayTags::Survivor_Status_Escaped)) Escape++;
				else Alive++;
			}			
		}
	}

	// 게임 내에 돌아다니는 생존자가 없고 Dead or Escape만 체크
	if (Alive == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("MMJ : Game End Success With Alive : %d, Dead : %d, Escape : %d "), Alive, Dead,
		       Escape);
		EndGameState();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MMJ : Game End Success With Alive : %d, Dead : %d, Escape : %d "), Alive, Dead, Escape );
	}
	
}

void ADBDGameMode::EndGameState()
{
	if (UDBDCharacterObserver* DBDCObserver = GetWorld()->GetSubsystem<UDBDCharacterObserver>())
	{
		if (DBDCObserver->GetSurvivors().Num() <= 0) return;
		
		for (TObjectPtr<ADBDCharacter> Character : DBDCObserver->GetSurvivors())
		{
			if (UAbilitySystemComponent* ASC = Character.Get()->GetAbilitySystemComponent())
			{
				ASC->AddLooseGameplayTag(DBDGameplayTags::Shared_GameState_End);
				ASC->AddReplicatedLooseGameplayTag(DBDGameplayTags::Shared_GameState_End);
			}			
		}
	}

	if (ADBDGameStateBase* GS = Cast<ADBDGameStateBase>(GameState))
	{
		GS->SetGameEnd(true);
		// FTimerHandle Timer;
		// GetWorld()->GetTimerManager().SetTimer(
		// 	Timer,
		// 	this,
		// 	&ThisClass::MoveToEndLevel,
		// 	3.f);
	}
}

void ADBDGameMode::MoveToEndLevel()
{
	GetWorld()->ServerTravel("/Game/_BP/MMJ/GameFlow/Level/EndGame", false, true);
}

void ADBDGameMode::DisplayEscapeWidget(bool IsDisplay)
{
	if (UDBDCharacterObserver* DBDCObserver = GetWorld()->GetSubsystem<UDBDCharacterObserver>())
	{
		if (DBDCObserver->GetSurvivors().Num() <= 0) return;
		
		for (TObjectPtr<ADBDCharacter> Character : DBDCObserver->GetSurvivors())
		{
			if (UAbilitySystemComponent* ASC = Character.Get()->GetAbilitySystemComponent())
			{
				//ASC->AddLooseGameplayTag(DBDGameplayTags::Shared_GameState_Escape);
				//ASC->AddReplicatedLooseGameplayTag(DBDGameplayTags::Shared_GameState_Escape);
			}			
		}
	}
}

