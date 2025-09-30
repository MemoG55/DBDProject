// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/DBDHUD_EndGame.h"

#include "AbilitySystemComponent.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Character/DBDCharacter.h"


void UDBDHUD_EndGame::NativeConstruct()
{
	Super::NativeConstruct();

	if (ADBDCharacter* Character = Cast<ADBDCharacter>(GetOwningPlayerPawn()))
	{
		if (UAbilitySystemComponent* ASC = Character->GetAbilitySystemComponent())
		{
			if (ASC->HasMatchingGameplayTag(DBDGameplayTags::Survivor_Status_Escaped))
			{
				
			}
		}
		
	}
}

void UDBDHUD_EndGame::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}
