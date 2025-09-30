// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Controller/DBDPlayerController.h"
#include "CommonActivatableWidget.h"
#include "GameFramework/HUD.h"
#include "Shared/Animation/DBDAnimInstance.h"
#include "Shared/Camera/DBDSpectatorCam.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/GameFramework/DBDGameStateBase.h"
#include "Shared/UI/DBDHUD_EndGame.h"

void ADBDPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (ADBDGameStateBase* GS = Cast<ADBDGameStateBase>(GetWorld()->GetGameState()))
	{
		if (GS->bIsGameEnded)
		{
			UE_LOG(LogTemp, Warning, TEXT("Ended True"));
		}
	}
}

void ADBDPlayerController::EnterSpectatorCam()
{
	if (IsLocalPlayerController())
	{
		SpectatorCam = GetWorld()->SpawnActor<ADBDSpectatorCam>(); // 커스텀 액터 (스프링암 + 카메라)
		if (!SpectatorCam)
		{
			return;
		}

		// 타깃 캐릭터에 붙이기
		SpectatorCam->AttachToActor(K2_GetPawn(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		SpectatorCam->SetActorRelativeLocation(FVector::ZeroVector);

		// ViewTarget 변경
		SetViewTarget(SpectatorCam);
	}
}

void ADBDPlayerController::CustomCreateWidget()
{
	if (ADBDCharacter* PlayerCharacter = Cast<ADBDCharacter>(GetCharacter()))
	{
		if (!IsValid(PlayerCharacter->HUD_EndGameClass)) return;

		if (UDBDHUD_EndGame* EndGameHUD = CreateWidget<UDBDHUD_EndGame>(this, PlayerCharacter->HUD_EndGameClass))
		{
			// TODO :: 뷰포트 체인지를 위해 Character쪽 공통 HUD를 가져올 필요가 있음.
			EndGameHUD->AddToViewport();
		}
	}
	
}

/*void ADBDPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PlayerCharacter = Cast<ADBDCharacter>(InPawn);
	if (PlayerCharacter)
	{
		PlayerCharacter->ServerSideInit();
	}
}*/

/*
void ADBDPlayerController::AcknowledgePossession(class APawn* P)
{
	Super::AcknowledgePossession(P);
	ADBDCharacter* DBDCharacter = Cast<ADBDCharacter>(P);
	if (!DBDCharacter)
	{
		return;
	}
	else
	{
		DBDCharacter->ClientSideInit();
	}
	if (!DBDCharacter->GetMesh())
	{
		return;
	}
	UDBDAnimInstance* DBDAnimInstance = Cast<UDBDAnimInstance>(DBDCharacter->GetMesh()->GetAnimInstance());
	if (DBDAnimInstance)
	{
		DBDAnimInstance->InitializeWithAbilitySystem(DBDCharacter->GetAbilitySystemComponent());
	}
}
*/
