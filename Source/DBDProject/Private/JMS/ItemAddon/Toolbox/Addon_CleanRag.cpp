// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/ItemAddon/Toolbox/Addon_CleanRag.h"

#include "JMS/Item/Toolbox/Item_Toolbox.h"


void UAddon_CleanRag::OnInitialized_Implementation()
{
	Cast<AItem_Toolbox>(GetOwningItem())->AddRepairSpeedMultiplier(.2f);
}
