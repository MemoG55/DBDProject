// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/KillerSkillHUD.h"
#include "Shared/DBDStruct.h"
#include "Shared/UI/AddonIcon.h"

void UKillerSkillHUD::SetAddonIcons(FItemAddonData Addon1, FItemAddonData Addon2)
{
	SkillAddonIcon1->SetAddOnImage(Addon1);
	SkillAddonIcon2->SetAddOnImage(Addon2);
}