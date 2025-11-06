// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Item/MedKit/Item_MedKit.h"

#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/GAS/ItemAbilitySystemComponent.h"
#include "Shared/DBDGameplayTags.h"
#include "JMS/GAS/AttributeSet/MedkitAttributeSet.h"


AItem_MedKit::AItem_MedKit()
{
	MedkitAttributeSet = CreateDefaultSubobject<UMedkitAttributeSet>(TEXT("MedkitAttributeSet"));
	ItemTag = DBDGameplayTags::Survivor_Item_MedKit;
}

void AItem_MedKit::OnEquipItem()
{
	Super::OnEquipItem();
	ASurvivorCharacter* OwnerSurvivor = Cast<ASurvivorCharacter>(GetOwner());
	if (OwnerSurvivor)
	{
		ItemAbilitySystemComponent->SetNumericAttributeBase(
			UMedkitAttributeSet::GetMedKitHealSpeedMultiplierAttribute(), 1.4f);
		ItemAbilitySystemComponent->SetNumericAttributeBase(
			UMedkitAttributeSet::GetMedKitSelfHealSpeedMultiplierAttribute(), 0.67f);
	}
}

void AItem_MedKit::OnInitialized_Implementation()
{
	Super::OnInitialized_Implementation();
}

void AItem_MedKit::OnStartUsingItem()
{
	Super::OnStartUsingItem();
}

void AItem_MedKit::OnEndUsingItem()
{
	Super::OnEndUsingItem();
}

void AItem_MedKit::BeginPlay()
{
	Super::BeginPlay();
}
