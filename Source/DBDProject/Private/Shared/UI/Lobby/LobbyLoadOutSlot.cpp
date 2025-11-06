// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/Lobby/LobbyLoadOutSlot.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Shared/Controller/DBDPlayerController.h"
#include "Shared/UI/Lobby/LobbyLoadOutSlotDesc.h"

ULobbyLoadOutSlot::~ULobbyLoadOutSlot()
{
	if (ADBDPlayerController* PC = GetOwningPlayer<ADBDPlayerController>())
	{
		OnLoadOutSlotClicked.RemoveAll(PC);
		OnLobbyLoadOutAddOnClicked.RemoveAll(PC);
		OnLobbyLoadOutItemClicked.RemoveAll(PC);
		OnLobbyLoadOutItemClicked.RemoveAll(PC);
	}
}

void ULobbyLoadOutSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (LoadOutRootButton)
	{
		LoadOutRootButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedSlot);
	}
	
}


void ULobbyLoadOutSlot::CreateToolTip(const FText& Text, const FText& ToolTip)
{
	//if (Text.EqualTo(FText()) || ToolTip.EqualTo(FText())) return;
	
	if (LoadOutSlotDesc && !SlotDesc)
	{
		SlotDesc = CreateWidget<ULobbyLoadOutSlotDesc>(GetOwningPlayer(), LoadOutSlotDesc);
	}

	if (IsValid(SlotDesc))
	{
		SlotDesc->SetData(Text, ToolTip);
		SetToolTip(SlotDesc);
	}
}

void ULobbyLoadOutSlot::HandleEmptyOverlay(ESlateVisibility PVisibility)
{
	if (SlotEmptyOverlay)
	{
		SlotEmptyOverlay->SetVisibility(PVisibility);	
	}
}

void ULobbyLoadOutSlot::HandleDataOverlay(ESlateVisibility PVisibility)
{
	if (SlotDataOverlay)
	{
		SlotDataOverlay->SetVisibility(PVisibility);	
	}
}

void ULobbyLoadOutSlot::SetDataImage(UTexture2D* ImageData)
{
	if (SlotDataImage)
	{
		FSlateBrush NewBrush;
		NewBrush.SetImageSize(FDeprecateSlateVector2D(200.f, 200.f));
		if (IsValid(ImageData))
		{
			NewBrush.SetResourceObject(ImageData);
			NewBrush.DrawAs = ESlateBrushDrawType::Type::Image;
			SlotDataImage->SetBrush(NewBrush);
			HandleDataOverlay(ESlateVisibility::Visible);
			HandleEmptyOverlay(ESlateVisibility::Hidden);
		}
		else
		{
			NewBrush.SetResourceObject(BlankImage);
			NewBrush.DrawAs = ESlateBrushDrawType::Type::NoDrawType;
			SlotDataImage->SetBrush(NewBrush);
			HandleDataOverlay(ESlateVisibility::Hidden);
			HandleEmptyOverlay(ESlateVisibility::Visible);
		}
	}	
}


void ULobbyLoadOutSlot::SetData(const FPerkData SlotData)
{
	SetDataImage(SlotData.Icon.Get());
	CreateToolTip(SlotData.DisplayName, SlotData.Description);
}

void ULobbyLoadOutSlot::SetData(const FItemData SlotData)
{
	SetDataImage(SlotData.Icon.Get());
	CreateToolTip(SlotData.DisplayName, SlotData.Description);
}

void ULobbyLoadOutSlot::SetData(const FItemAddonData SlotData)
{
	SetDataImage(SlotData.Icon.Get());
	CreateToolTip(SlotData.DisplayName, SlotData.Description);
}



void ULobbyLoadOutSlot::OnClickedSlot()
{
	if (CurrentSlotType == ELobbyLoadOutSlotType::Perk && PerkData && DataRowName.IsValid())
	{
		OnLobbyLoadOutPerkClicked.Broadcast(DataRowName, *PerkData);
	}
	else if (CurrentSlotType == ELobbyLoadOutSlotType::Item && ItemData && DataRowName.IsValid())
	{
		OnLobbyLoadOutItemClicked.Broadcast(DataRowName, *ItemData);
	}
	else if (CurrentSlotType == ELobbyLoadOutSlotType::AddOn && ItemAddonData && DataRowName.IsValid())
	{
		OnLobbyLoadOutAddOnClicked.Broadcast(DataRowName, *ItemAddonData);
	}
	OnLoadOutSlotClicked.Broadcast(CurrentSlotType);
}

void ULobbyLoadOutSlot::SetSlotType(ELobbyLoadOutSlotType Type)
{
	CurrentSlotType = Type;
	switch (Type)
	{
	case ELobbyLoadOutSlotType::Perk:
		SlotBackgroundImage->SetBrushFromTexture(BackgroundImage_Perk);
		break;
	case ELobbyLoadOutSlotType::Item:
		SlotBackgroundImage->SetBrushFromTexture(BackgroundImage_Item);
		break;
	case ELobbyLoadOutSlotType::AddOn:
		SlotBackgroundImage->SetBrushFromTexture(BackgroundImage_AddOn);
		break;
	default:
		break;
	}
}

ELobbyLoadOutSlotType ULobbyLoadOutSlot::GetSlotType()
{
	return CurrentSlotType;
}
