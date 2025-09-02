// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Character/DBDCharacter.h"
#include "AbilitySystemInterface.h"
#include "Shared/GameFramework/DBDPlayerState.h"

UAbilitySystemComponent* ADBDCharacter::GetAbilitySystemComponent() const
{
	IAbilitySystemInterface* PSASInterface = Cast<IAbilitySystemInterface>(GetPlayerState());
	if (PSASInterface)
	{
		return PSASInterface->GetAbilitySystemComponent();
	}
	return nullptr;
}
