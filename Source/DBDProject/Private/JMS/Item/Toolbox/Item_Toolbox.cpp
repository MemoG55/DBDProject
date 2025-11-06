// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Item/Toolbox/Item_Toolbox.h"

#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/GAS/ItemAbilitySystemComponent.h"
#include "JMS/GAS/SurvivorAbilitySystemComponent.h"
#include "JMS/GAS/SurvivorAttributeSet.h"
#include "JMS/GAS/AttributeSet/ToolboxAttributeSet.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDGameplayTags.h"


AItem_Toolbox::AItem_Toolbox()
{
	ToolboxAttributeSet = CreateDefaultSubobject<UToolboxAttributeSet>(TEXT("ToolboxAttributeSet"));
	ItemTag = DBDGameplayTags::Survivor_Item_Toolbox;
}

void AItem_Toolbox::OnEquipItem()
{
	Super::OnEquipItem();
	ASurvivorCharacter* OwnerSurvivor = Cast<ASurvivorCharacter>(GetOwner());
	if (OwnerSurvivor)
	{
		// ItemAbilitySystemComponent->SetNumericAttributeBase(
		// 	UToolboxAttributeSet::GetToolboxRepairSpeedMultiplierAttribute(), RepairSpeedMultiplier);
		// ItemAbilitySystemComponent->SetNumericAttributeBase(
		// 	UToolboxAttributeSet::GetToolboxSabotageSpeedMultiplierAttribute(), SabotageSpeedMultiplier);
	}
}

void AItem_Toolbox::OnInitialized_Implementation()
{
	Super::OnInitialized_Implementation();
}

void AItem_Toolbox::OnStartUsingItem()
{
	Super::OnStartUsingItem();
}

void AItem_Toolbox::OnEndUsingItem()
{
	Super::OnEndUsingItem();
}

void AItem_Toolbox::BeginPlay()
{
	Super::BeginPlay();

	
}
