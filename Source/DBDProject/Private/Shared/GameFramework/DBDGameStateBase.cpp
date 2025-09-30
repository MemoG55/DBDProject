// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/GameFramework/DBDGameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "MMJ/Object/Interactable/DBDObject.h"
#include "MMJ/Object/GAS/ObjAbilitySystemComponent.h"
#include "MMJ/Object/Interactable/Obj_ExitDoor.h"
#include "MMJ/Object/Interactable/Obj_Generator.h"
#include "Net/UnrealNetwork.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDEnum.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/Component/InteractableComponent.h"
#include "Shared/Controller/DBDPlayerController.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/UI/DBDHUD.h"

ADBDGameStateBase::ADBDGameStateBase()
{
	bReplicates = true;
}

void ADBDGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ADBDGameStateBase, EscapeTimer, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ADBDGameStateBase, RemainingEscapeTime, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ADBDGameStateBase, bIsGameEnded, COND_None, REPNOTIFY_Always);
}


float ADBDGameStateBase::GetMaxEscapeTime()
{
	return MaxEscapeTime;
}

void ADBDGameStateBase::SetEscapeTimer()
{
	if (!EscapeTimer.IsValid() && HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimer(EscapeTimer,
			this,
			&ThisClass::TickEscapeTimer,
		EscapeTimerInterval,
		true);

	}
}

void ADBDGameStateBase::TickEscapeTimer()
{
	if (RemainingEscapeTime <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(EscapeTimer);

		if (HasAuthority())
		{
			OnEscapeTimerEnd.Broadcast();
		}
		
		return;
	}
	RemainingEscapeTime -= EscapeTimerInterval;
}

void ADBDGameStateBase::OnRep_RemainingEscapeTime()
{
	OnEscapeTimer.Broadcast(RemainingEscapeTime);
}

void ADBDGameStateBase::OnRep_EscapeTimer()
{
	if (EscapeTimer.IsValid())
	{
		OnEscapeTimerBegin.Broadcast();
	}
}

void ADBDGameStateBase::SetGameEnd(bool Result)
{
	GetWorld()->GetTimerManager().ClearTimer(EscapeTimer);
	bIsGameEnded = Result;
}

void ADBDGameStateBase::OnRep_bIsGameEnded()
{
	//MoveToEndGameLevel();
	for (const APlayerState* PS : PlayerArray)
	{
		if (ADBDPlayerController* PC = Cast<ADBDPlayerController>(PS->GetPlayerController()))
		{
			if (PC->IsLocalPlayerController())
			{
				PC->CustomCreateWidget();
			}
		}
	}
}


void ADBDGameStateBase::MoveToEndGameLevel_Implementation()
{
	GetWorld()->ServerTravel("/Game/_BP/MMJ/GameFlow/Level/EndGame", false, true);
}

void ADBDGameStateBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ADBDGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		// 발전기
		{
			TArray<AActor*> FoundActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AObj_Generator::StaticClass(), FoundActors);
			for (AActor* Actor : FoundActors)
			{
				if (AObj_Generator* Generator = Cast<AObj_Generator>(Actor))
				{
					Generators.Add(Generator);

					if (Generator->GetInteractableComponent())
					{
						Generator->GetInteractableComponent()->OnComplete.AddDynamic(this, &ThisClass::ADBDGameStateBase::CheckGeneratorState);
					}
				}
			}
		}
		
		// 탈출구
		{
			TArray<AActor*> FoundActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AObj_ExitDoor::StaticClass(), FoundActors);
			for (AActor* Actor : FoundActors)
			{
				if (AObj_ExitDoor* ExitDoor = Cast<AObj_ExitDoor>(Actor))
				{
					ExitDoor->GetInteractableComponent()->OnComplete.AddDynamic(this, &ThisClass::SetEscapeTimer);
					ExitDoors.Add(ExitDoor);
				}
			}
		}
	}
}

int32 ADBDGameStateBase::GetRequiredGeneratorCount()
{
	// 플레이어 생존자 수 구하기 + 1 = 발전기 요구 수량
	return GetSurvivorCount() + 1; 
}

void ADBDGameStateBase::CheckGeneratorState()
{
	if (!HasAuthority()) return;
	
	int32 RepairCount = 0;
	for (ADBDObject* Generator : Generators)
	{
		if (UDBDBlueprintFunctionLibrary::NativeActorHasTag(Generator, DBDGameplayTags::Object_Status_IsComplete))
		{
			RepairCount++;
		}
	}

	RepairGeneratorCount = RepairCount;
	
	if (RepairCount >= GetRequiredGeneratorCount())
	{
		// 발전기들이 수리요구수량만큼 수리되었을 때 실행될 알림 전송 함수 필요
		Debug::Print(TEXT("ExitDoor IS Accessible"), 12);
	}
}

int32 ADBDGameStateBase::GetSurvivorCount()
{
	int32 SurvivorCount = 0;
	EPlayerRole SurvivorRole = EPlayerRole::Survivor;
	for (APlayerState* PS : PlayerArray)
	{
		if (ADBDPlayerState* DBDPS = Cast<ADBDPlayerState>(PS))
		{
			if (DBDPS->GetPlayerRole() == SurvivorRole)
			{
				SurvivorCount++;
			}
		}
	}
	return SurvivorCount;
}

int32 ADBDGameStateBase::GetRepairGeneratorCount()
{
	return RepairGeneratorCount;
}
