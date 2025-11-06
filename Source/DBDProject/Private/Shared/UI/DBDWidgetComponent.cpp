// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/DBDWidgetComponent.h"

#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/UI/SurvivorHUD.h"
#include "KMJ/Character/KillerCharacter.h"
#include "KMJ/UI/KillerHUD.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/GameFramework/DBDPlayerState.h"


UDBDWidgetComponent::UDBDWidgetComponent()
{
}

void UDBDWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle TimerHandle;
	// JMS: UI수정: 3초 뒤 스폰
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this, &UDBDWidgetComponent::LateWidgetInitialization, 3.0f);
	// if (!PlayerCharacter)
	// {
	// 	PlayerCharacter = Cast<ADBDCharacter>(GetOwner());
	// }
	// // JMS: UI수정: CreateWidget 후 Owner 부여
	// if (PlayerCharacter && PlayerCharacter->IsLocallyControlled())
	// {
	// 	PlayerHUD = CreateWidget<UDBDHUD>(PlayerCharacter->GetController<APlayerController>(), PlayerHUDClass);
	// 	PlayerHUD->AddToViewport();
	// 	PlayerCharacter->AbilityWidgetUpdate.AddDynamic(this, &UDBDWidgetComponent::UpdateAbilityWidget);
	// 	PlayerCharacter->AbilityNameOnlyWidgetUpdate.
	// 	                 AddDynamic(this, &UDBDWidgetComponent::UpdateAbilityNameOnlyWidget);
	// }
	// PlayerHUD = PlayerCharacter->PlayerHUD;
	// PlayerCharacter->OnPerkUIInitialize.AddDynamic(this, &UDBDWidgetComponent::InitializePerkWidget);
	// PlayerCharacter->OnItemUIInitialize.AddDynamic(this, &UDBDWidgetComponent::InitializePlayerItemSkillWidget);
}

void UDBDWidgetComponent::LateWidgetInitialization()
{
	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<ADBDCharacter>(GetOwner());
	}
	// JMS: UI수정: CreateWidget 후 Owner 부여
	if (ADBDPlayerState* PS = PlayerCharacter->GetPlayerState<ADBDPlayerState>())
	{
		if (PS->GetPlayerEndState() != EPlayerEndState::None) return;
		
		if (PlayerCharacter && PlayerCharacter->IsLocallyControlled())
		{
			UE_LOG(LogTemp, Warning, TEXT("MMJLog : HUD Set"));
			PlayerHUD = CreateWidget<UDBDHUD>(PlayerCharacter->GetController<APlayerController>(), PlayerHUDClass);
			PlayerHUD->AddToViewport();
		}
	}
}

//
// void UDBDWidgetComponent::InitializePerkWidget()
// {
// 	PlayerHUD = Character->PlayerHUD;
// 	if (PlayerHUD)
// 	{
// 		//Debug::Print(TEXT("***UDBDWidgetComponent::SetPlayerHUD"), 343);
// 		PlayerHUD->AddToViewport();
// 		PlayerHUD->SetPerkUIHUD(Character, PlayerRole);
// 		
// 	}
// 	else
// 	{
// 		//Debug::Print(TEXT("***UDBDWidgetComponent::SetPlayerHUD:: PlayerHUD NOT Valid"), 343);
// 	}
// 	// JMS: UI수정: 수정했는데 안 써도 될듯
// 	if (PlayerHUD)
// 	{
// 		PlayerHUD->InitializePerkWidget();
// 	}
// }

// void UDBDWidgetComponent::InitializePlayerItemSkillWidget()
// {
// 	//Item Initialize
// 	if (!IsValid(Character))
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("SetPlayerItemSkillHUD: Character is null"));
// 		return;
// 	}
// 	
// 	if (Character->PlayerHUD)
// 	{
// 		//Debug::Print(TEXT("***UDBDWidgetComponent::SetPlayerItemSkillHUD:: PlayerHUD Valid"), 355);
// 		PlayerHUD = Character->PlayerHUD;
// 		if (!Character->PlayerHUD->IsInViewport())
// 		{
// 			Character->PlayerHUD->AddToViewport();
// 		}
// 		Character->PlayerHUD->SetItemHUD(Character);
// 	}
// 	else
// 	{
// 		//Debug::Print(TEXT("***UDBDWidgetComponent::SetPlayerItemSkillHUD:: PlayerHUD NOT Valid"), 343);
// 	}
// }