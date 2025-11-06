// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/ItemAddon/Toolbox/Addon_Scraps.h"
#include "JMS/Item/Toolbox/Item_Toolbox.h"


void UAddon_Scraps::OnInitialized_Implementation()
{
	GetOwningItem()->AddMaxCharge(8);
	GetOwningItem()->AddCurrentCharge(8);
}
