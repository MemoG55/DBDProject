// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/GAS/GA/DBDGameplayAbility.h"

#include "Shared/Character/DBDCharacter.h"

UDBDWidgetComponent* UDBDGameplayAbility::GetDBDWidgetComponentFromActorInfo() const
{
	if (IsValid(GetDBDCharacterFromActorInfo()))
	{
		return GetDBDCharacterFromActorInfo()->GetWidgetComponent();
	}
	return nullptr;
}

ADBDCharacter* UDBDGameplayAbility::GetDBDCharacterFromActorInfo() const
{
	return Cast<ADBDCharacter>(GetAvatarActorFromActorInfo());
}


