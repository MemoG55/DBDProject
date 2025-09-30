// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Perk/PerkInstance.h"

#include "Shared/Character/DBDCharacter.h"


void UPerkInstance::OnInitialized()
{
}

ADBDCharacter* UPerkInstance::GetOuterAsDBDCharacter()
{
	return CastChecked<ADBDCharacter>(GetOuter());
}
