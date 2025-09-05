// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/GameFramework/DBDGameMode.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/GameStateBase.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/GameFramework/DBDPlayerState.h"

ADBDGameMode::ADBDGameMode()
{
}

void ADBDGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ADBDGameMode::PostLogin(APlayerController* NewPlayer)
{
	if (ADBDPlayerState* PS = NewPlayer->GetPlayerState<ADBDPlayerState>())
	{
		int32 CurrentCount = GameState->PlayerArray.Num();
		if (CurrentCount == 1) // 첫 번째 플레이어
		{
			PS->SetPlayerRole(EPlayerRole::Killer);
			PS->AuthInitAttributeSet();
		}
		else
		{
			PS->SetPlayerRole(EPlayerRole::Survivor);
			PS->AuthInitAttributeSet();
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
	UE_LOG(LogTemp, Warning, TEXT("JMS : %s : PlayerRole: %s"), *GetNameSafe(this),
	       *(StaticEnum<EPlayerRole>()->GetNameStringByValue((int64)(PS->GetPlayerRole()))));
	// 역할 별 캐릭터 스폰, ASC 초기화 후 Possess
	if (PS->GetPlayerRole() == EPlayerRole::Killer)
	{
		APawn* KillerPawn = GetWorld()->SpawnActor<APawn>(KillerCharacterClass,
		                                                  ChoosePlayerStart(NewPlayer)->GetActorTransform());
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(this, KillerPawn);
		NewPlayer->Possess(KillerPawn);
	}
	else
	{
		APawn* SurvivorPawn = GetWorld()->SpawnActor<APawn>(SurvivorCharacterClass,
		                                                    ChoosePlayerStart(NewPlayer)->GetActorTransform());
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(this, SurvivorPawn);
		NewPlayer->Possess(SurvivorPawn);
	}
}

void ADBDGameMode::TEST()
{
}
