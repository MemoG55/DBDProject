// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Subsystem/DBDEndGameSubsystem.h"

#include "Shared/GameFramework/DBDGameMode.h"
#include "Shared/GameFramework/DBDGameStateBase.h"

void UDBDEndGameSubsystem::StartEscapeTimer()
{
	RemainingTime = EscapeDuration;
	if (!EscapeTimer.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(
			EscapeTimer,
			this,
			&ThisClass::TickEscapeTimer,
			0.1f,
			true);
	}
	OnEndGameStart.Broadcast();
}

void UDBDEndGameSubsystem::SetTimerSlow(bool bIsSlowCond)
{
	bIsSlow = bIsSlowCond;
}

void UDBDEndGameSubsystem::TickEscapeTimer()
{
	if (bIsSlow)
	{
		RemainingTime -= SlowTimerSpeed;
	}
	else
	{
		RemainingTime -= NormalTimerSpeed;
	}
		
	if (ADBDGameStateBase* GS = GetWorld()->GetGameState<ADBDGameStateBase>())
	{
		GS->SetRemainingEscapeTime(RemainingTime);
	}
	if (RemainingTime <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(EscapeTimer);
		if (ADBDGameMode* GM = GetWorld()->GetAuthGameMode<ADBDGameMode>())
		{
			GM->EndGameState();
		}
	}
}
