// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Controller/DBDPlayerController.h"
#include "CommonActivatableWidget.h"
#include "Shared/Animation/DBDAnimInstance.h"
#include "Shared/Character/DBDCharacter.h"

void ADBDPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (UIBaseClass)
	{
		UIBase = CreateWidget<UCommonActivatableWidget>(this,UIBaseClass);
		UIBase->AddToViewport();
	}
	SetInputMode(FInputModeGameOnly());
}

void ADBDPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
}

void ADBDPlayerController::AcknowledgePossession(class APawn* P)
{
	Super::AcknowledgePossession(P);
	ADBDCharacter* DBDCharacter = Cast<ADBDCharacter>(P);
	if (!DBDCharacter)
	{
		return;
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
