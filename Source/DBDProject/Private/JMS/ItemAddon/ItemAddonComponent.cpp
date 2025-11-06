// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/ItemAddon/ItemAddonComponent.h"

#include "AbilitySystemComponent.h"

// Sets default values for this component's properties
UItemAddonComponent::UItemAddonComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	// ...
}


// Called when the game starts
void UItemAddonComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

FName UItemAddonComponent::GetAddonID() const
{
	return AddonID;
}

void UItemAddonComponent::OnInitialized_Implementation()
{
	// 자식에서 구현
}


void UItemAddonComponent::OnUnEquip_Implementation()
{
	UAbilitySystemComponent* ASC = GetOwningItem()->GetAbilitySystemComponent();
	if (ASC)
	{
		for (TSubclassOf<UGameplayEffect> AddonEffect : AddonEffects)
		{
			ASC->RemoveActiveGameplayEffectBySourceEffect(AddonEffect, ASC);
		}
	}
}

void UItemAddonComponent::OnEquip_Implementation()
{
	UAbilitySystemComponent* ASC = GetOwningItem()->GetAbilitySystemComponent();
	if (ASC)
	{
		for (TSubclassOf<UGameplayEffect> AddonEffect : AddonEffects)
		{
			ASC->BP_ApplyGameplayEffectToSelf(AddonEffect, 0, ASC->MakeEffectContext());
		}
	}
}
