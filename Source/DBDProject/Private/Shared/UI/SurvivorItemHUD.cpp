// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/SurvivorItemHUD.h"

#include "Shared/DBDStruct.h"
#include "Shared/UI/AddonIcon.h"

//
// void USurvivorItemHUD::SetAddonIcons(FItemAddonData Addon1, FItemAddonData Addon2)
// {
// 	AddonIcon1->SetAddOnImage(Addon1);
// 	AddonIcon2->SetAddOnImage(Addon2);
// }
void USurvivorItemHUD::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Visible);
}
