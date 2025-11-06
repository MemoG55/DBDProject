// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/GameFramework/End/EndGameMode.h"

#include "Camera/CameraActor.h"
#include "Engine/AssetManager.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerStart.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/DataAsset/DBDDataBase.h"
#include "Shared/GameFramework/DBDGameInstance.h"
#include "Shared/GameFramework/DBDPlayerState.h"

AEndGameMode::AEndGameMode()
{
	bUseSeamlessTravel = true;
}

void AEndGameMode::GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList)
{
	Super::GetSeamlessTravelActorList(bToTransition, ActorList);
}

void AEndGameMode::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();
}

void AEndGameMode::HandleSeamlessTravelPlayer(AController*& C)
{
	Super::HandleSeamlessTravelPlayer(C);

	
	if (APlayerController* PC = Cast<APlayerController>(C))
	{
		if (ADBDPlayerState* PS = PC->GetPlayerState<ADBDPlayerState>())
		{
			UE_LOG(LogTemp, Warning, TEXT("MMJLog : %s , EndState : %s"), *PS->GetPlayerName(), *UEnum::GetValueAsString(PS->GetPlayerEndState()));	
		}
	}
}

void AEndGameMode::SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC)
{
	Super::SwapPlayerControllers(OldPC, NewPC);
}

void AEndGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	ADBDPlayerState* PS = NewPlayer->GetPlayerState<ADBDPlayerState>();
	if (!PS)
	{
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ACameraActor::StaticClass(), TEXT("EndGameCamera"), CameraActors);

	ACameraActor* TargetCamera = nullptr;
	
	
	if (PS->GetPlayerRole() == EPlayerRole::Killer)
	{
		if (!KillerCharacterClass)
		{
			return;
		}
		APawn* KillerPawn = GetWorld()->SpawnActor<APawn>(KillerCharacterClass, FTransform::Identity, SpawnParams);
		NewPlayer->Possess(KillerPawn);

		if (CameraActors.Num() > 0)
		{
			// 찾은 첫 번째 카메라를 사용
			TargetCamera = Cast<ACameraActor>(CameraActors[0]);
			if (TargetCamera)
			{
				NewPlayer->SetViewTargetWithBlend(TargetCamera, 0.f);
			}
		}
	}
	else
	{
		if (SurvivorPlayerStarts.IsEmpty())
		{
			return;
		}

		if (!SurvivorPlayerStarts.IsValidIndex(SurvivorSpawnCurrentIndex)) return;
		FTransform SurvivorSpawnTransform = SurvivorPlayerStarts[SurvivorSpawnCurrentIndex]->GetTransform();

		APawn* SurvivorPawn = SpawnSurvivorCharacter(PS, SurvivorSpawnTransform);
		SurvivorSpawnCurrentIndex++;

		NewPlayer->Possess(SurvivorPawn);
		if (CameraActors.Num() > 0)
		{
			// 찾은 첫 번째 카메라를 사용
			TargetCamera = Cast<ACameraActor>(CameraActors[1]);
			if (TargetCamera)
			{
				NewPlayer->SetViewTargetWithBlend(TargetCamera, 0.f);
			}
		}
	}
	DisableInput(NewPlayer);
}

AActor* AEndGameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	TArray<AActor*> PlayerStartActors;
	UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStartActors);
	if (PlayerStartActors.IsEmpty())
	{
		return nullptr;
	}
	TArray<APlayerStart*> PlayerStarts;
	for (AActor* PlayerStartActor : PlayerStartActors)
	{
		APlayerStart* PlayerStart = Cast<APlayerStart>(PlayerStartActor);
		PlayerStarts.Add(PlayerStart);
	}

	if (ADBDPlayerState* PS = Player->GetPlayerState<ADBDPlayerState>())
	{
		if (PS->GetPlayerRole() == EPlayerRole::Killer)
		{
			// KillerStart
			TArray<APlayerStart*> KillerPlayerStarts;
			for (APlayerStart* PlayerStart : PlayerStarts)
			{
				if (PlayerStart->PlayerStartTag == FName("Killer"))
				{
					KillerPlayerStarts.Add(PlayerStart);
				}
			}
			if (KillerPlayerStarts.IsEmpty())
			{
				return nullptr;
			}

			int32 KillerSpawnRandomIndex = FMath::RandRange(0, KillerPlayerStarts.Num() - 1);
			APlayerStart* KillerPlayerStart = KillerPlayerStarts[KillerSpawnRandomIndex];
			return KillerPlayerStart;
		}
		else
		{
			//YHG : PlayerStart Spawn Logic -> MMJ Encoding Error Change to English
			//The first PlayerStart  in a group of 4
			
			for (APlayerStart* PlayerStart : PlayerStarts)
			{
				if (PlayerStart->PlayerStartTag == FName("Survivor"))
				{
					SurvivorPlayerStarts.Add(PlayerStart);
				}
			}
			if (SurvivorPlayerStarts.IsEmpty())
			{
				return nullptr;
			}
			int32 SurvivorSpawnStartIndex = 0;
			for (APlayerState* ExsistPS : GameState->PlayerArray)
			{
				if (ADBDPlayerState* DBDPS = Cast<ADBDPlayerState>(ExsistPS))
				{
					if (DBDPS->GetPlayerRole() == EPlayerRole::Survivor)
					{
						if (DBDPS->GetPlayerController()->IsLocalController())
						{
							break;
						}

						SurvivorSpawnStartIndex++;
					}
				}
			}
			return SurvivorPlayerStarts[SurvivorSpawnStartIndex];
		}
	}
	
	return Super::FindPlayerStart_Implementation(Player, IncomingName);
}


ASurvivorCharacter* AEndGameMode::SpawnSurvivorCharacter(ADBDPlayerState* DBDPS, FTransform SpawnTransform)
{
	UDBDGameInstance* DBDGI = Cast<UDBDGameInstance>(GetGameInstance());
	if (!DBDGI || !DBDPS)
	{
		return nullptr;
	}
	UDataTable* DT = Cast<UDataTable>(
		UAssetManager::Get().GetStreamableManager().LoadSynchronous(
			DBDGI->DBDDB->SurvivorCharacterDB.ToSoftObjectPath()));

	ASurvivorCharacter* SpawnedSurvivor = nullptr;

	if (DT)
	{
		
		FSurvivorCharacterData* SurvivorData = DT->FindRow<
			FSurvivorCharacterData>(DBDPS->SurvivorLoadout.Character, "");
		if (SurvivorData)
		{
			TSubclassOf<ASurvivorCharacter> SurvivorClassFromDB = SurvivorData->CharacterClass;
			if (SurvivorClassFromDB)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnedSurvivor = GetWorld()->SpawnActor<ASurvivorCharacter>(
					SurvivorClassFromDB, SpawnTransform, SpawnParams);
				return SpawnedSurvivor;
			}
		}
	}
	return SpawnedSurvivor;
}

void AEndGameMode::HandleExit(APlayerController* PC)
{
	if (PC)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), PC, EQuitPreference::Type::Quit, true);		
	}
}
