// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/DBDHUD_EndGame.h"

#include "AbilitySystemComponent.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/Controller/EndPlayerController.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/GAS/DBDAbilitySystemComponent.h"


void UDBDHUD_EndGame::NativeConstruct()
{
	Super::NativeConstruct();

	if (ADBDPlayerState* PS = GetOwningPlayerState<ADBDPlayerState>())
	{
		if (PS->GetPlayerRole() == EPlayerRole::Killer)
		{
			TextblockText = "Entity Is Hungry..";
		}
		else
		{
			TextblockText = PS->GetPlayerEndState() == EPlayerEndState::Escape ? FString("Escaped..") : FString("Sacrificed..");
		}
		IsEscaped->SetText(FText::FromString(TextblockText));
	}
}

void UDBDHUD_EndGame::BindingPlayerController()
{
	if (AEndPlayerController* PC = Cast<AEndPlayerController>(GetOwningPlayer()))
	{
		if (ExitButton)
		{
			ExitButton->OnClicked.AddDynamic(PC, &AEndPlayerController::RequestExit);
		}
	}
}
