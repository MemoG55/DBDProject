// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/BaseSquareIcon.h"

#include "Components/Image.h"
#include "Shared/DBDEnum.h"

void UBaseSquareIcon::ClearIcon()
{
	IconImage = nullptr;
	FColor sRGBColor(255, 255, 255, 255);
	IconLevelImage->SetColorAndOpacity(FLinearColor::FromSRGBColor(sRGBColor));
}

void UBaseSquareIcon::SetIconLevel(ETier Tier)
{
	if (IconLevelImage)
	{
		if (Tier == ETier::Green)
		{
			// Green (RGB: 7, 64, 16)
			FColor sRGBColor(7, 64, 16, 255);
			IconLevelImage->SetColorAndOpacity(FLinearColor::FromSRGBColor(sRGBColor));
		}
		else if (Tier == ETier::Yellow)
		{
			// Yellow (RGB: 193, 163, 73)
			FColor sRGBColor(193, 163, 73, 255);
			IconLevelImage->SetColorAndOpacity(FLinearColor::FromSRGBColor(sRGBColor));
		}
		else if (Tier == ETier::Purple)
		{
			// Purple (RGB: 134, 97, 149)
			FColor sRGBColor(134, 97, 149, 255);
			IconLevelImage->SetColorAndOpacity(FLinearColor::FromSRGBColor(sRGBColor));
		}
		else if (Tier == ETier::Red)
		{
			// Red (RGB: 128, 0, 40)
			FColor sRGBColor(128, 0, 40, 255);
			IconLevelImage->SetColorAndOpacity(FLinearColor::FromSRGBColor(sRGBColor));
		}
		else if (Tier == ETier::Blue)
		{
			// Blue (RGB: 47, 156, 214)
			FColor sRGBColor(47, 156, 214, 255);
			IconLevelImage->SetColorAndOpacity(FLinearColor::FromSRGBColor(sRGBColor));
		}
		else
		{
			// Brown (RGB: 94, 63, 33)
			FColor sRGBColor(94, 63, 33, 255);
			IconLevelImage->SetColorAndOpacity(FLinearColor::FromSRGBColor(sRGBColor));
		}

	}
}
