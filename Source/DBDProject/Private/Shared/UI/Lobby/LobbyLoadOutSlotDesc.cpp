// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/Lobby/LobbyLoadOutSlotDesc.h"

#include "Components/TextBlock.h"


void ULobbyLoadOutSlotDesc::SetData(const FText& PDisplayName, const FText& PDescription)
{
	if (DisplayName)
	{
		DisplayName->SetText(PDisplayName);
	}
	if (Description)
	{
		Description->SetText(PDescription);
	}
}

UTextBlock* ULobbyLoadOutSlotDesc::GetDescription()
{
	return Description;
}

UTextBlock* ULobbyLoadOutSlotDesc::GetDisplayName()
{
	return DisplayName;
}
