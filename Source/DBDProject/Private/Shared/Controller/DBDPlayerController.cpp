// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Controller/DBDPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/Camera/DBDSpectatorCam.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/UI/DBDHUD.h"
#include "Shared/UI/DBDWidgetComponent.h"
#include "Sound/SoundCue.h"

ADBDPlayerController::ADBDPlayerController()
{
	bNetLoadOnClient = true;
}

void ADBDPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void ADBDPlayerController::EnterSpectatorCam()
{
	SpectatorCam = GetWorld()->SpawnActor<ADBDSpectatorCam>(); // 커스텀 액터 (스프링암 + 카메라)
	if (!SpectatorCam)
	{
		return;
	}

	// 타깃 캐릭터에 붙이기
	SpectatorCam->AttachToActor(GetPawn(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SpectatorCam->SetActorRotation(FRotator(0.f, 180.f, 0.f));
	
	// ViewTarget 변경
	FViewTargetTransitionParams TransitionParams;
	TransitionParams.BlendTime = 0.5f;
	
	ClientSetViewTarget(SpectatorCam, TransitionParams);
}

void ADBDPlayerController::ExitSpectatorCam()
{
	bIsSetSpectatorCam = false;
	FInputModeGameOnly EnableGameMode;
	SetInputMode(EnableGameMode);
	FTimerHandle SpectatorCamTimerHandle;
	GetWorldTimerManager().SetTimer(
		SpectatorCamTimerHandle,
		FTimerDelegate::CreateLambda([&]
		{
			FViewTargetTransitionParams TransitionParams;
			TransitionParams.BlendTime = 0.5f;
			ClientSetViewTarget(GetCharacter(), TransitionParams);
			GetCharacter()->EnableInput(this);
		}),
		1.f,
		false);
}


void ADBDPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsSetSpectatorCam && SpectatorCam && GetCharacter())
	{
		if (CurrentYaw <= -180.f)
		{
			ExitSpectatorCam();
			return;
		}
		CurrentYaw -= DeltaSeconds * 40.f;
	
		FRotator CurrentRotation = FRotator(0.f, CurrentYaw, 0.f);
		FVector InitialOffset = FVector(200.f, 0.f, 0.f);
		FVector RelativeOffset = CurrentRotation.RotateVector(InitialOffset);
		FVector CharacterLocation = GetCharacter()->GetActorLocation();
		FVector FinalLocation = CharacterLocation + RelativeOffset;

		FRotator FinalRotation = UKismetMathLibrary::FindLookAtRotation(FinalLocation, CharacterLocation);

		SpectatorCam->SetActorLocation(FinalLocation);
		SpectatorCam->SetActorRotation(FinalRotation);
	}
}

void ADBDPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

void ADBDPlayerController::AcknowledgePossession(class APawn* P)
{
	Super::AcknowledgePossession(P);
	SetPause(true);
	LoadingWidget = CreateWidget<UUserWidget>(GetWorld(), LoadingWidgetClass);
	LoadingWidget->AddToViewport();
	FTimerHandle StartTimerHandle;
	GetWorldTimerManager().SetTimer(StartTimerHandle,this,&ADBDPlayerController::StartAfterWait, 3.f, false);
	
	
}

void ADBDPlayerController::StartAfterWait()
{
	SetPause(false);
	LoadingWidget->RemoveFromParent();
	UGameplayStatics::PlaySound2D(GetWorld(), StartMusicCue);
	EnterSpectatorCam();
	FTimerHandle SpectatorCamStartTimerHandle;
	GetWorldTimerManager().SetTimer(
		SpectatorCamStartTimerHandle,
		FTimerDelegate::CreateLambda([&]
		{
			bIsSetSpectatorCam = true;
		}),
		1.f,
		false);
}

void ADBDPlayerController::DisplayProgressUI_Implementation(UDBDAbilitySystemComponent* ASC)
{
	if (ADBDCharacter* PlayerCharacter = Cast<ADBDCharacter>(GetCharacter()))
	{
		
		if (UDBDWidgetComponent* PlayerWidgetComponent = PlayerCharacter->GetWidgetComponent())
		{
			PlayerWidgetComponent->PlayerHUD->SetProgressHUD(ASC);
		}
	}
}

