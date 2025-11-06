// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Perk/Perk_SprintBurst.h"

#include "AbilitySystemComponent.h"
#include "JMS/Character/SurvivorCharacter.h"


UPerk_SprintBurst::UPerk_SprintBurst()
{
	PerkID = FName(TEXT("SprintBurst"));
}

void UPerk_SprintBurst::OnServerSideInitialized()
{
	Super::OnServerSideInitialized();
	ASurvivorCharacter* OwnerSurvivorCharacter = Cast<ASurvivorCharacter>(GetOuterAsDBDCharacter());
	if (OwnerSurvivorCharacter)
	{
		OwnerSurvivorCharacter->OnSprintStartedDelegate.AddDynamic(this, &UPerk_SprintBurst::OnSprintStarted);
	}
}

void UPerk_SprintBurst::OnOwnerClientSideInitialized()
{
	Super::OnOwnerClientSideInitialized();
}

void UPerk_SprintBurst::OnSprintStarted()
{
	if (SprintBurstEffect)
	{
		GetOuterAsDBDCharacter()->GetAbilitySystemComponent()->BP_ApplyGameplayEffectToSelf(
			SprintBurstEffect, 0, GetOuterAsDBDCharacter()->GetAbilitySystemComponent()->MakeEffectContext());
		if (ExhaustEffect)
		{
			GetOuterAsDBDCharacter()->GetAbilitySystemComponent()->BP_ApplyGameplayEffectToSelf(
				ExhaustEffect, 0, GetOuterAsDBDCharacter()->GetAbilitySystemComponent()->MakeEffectContext());
		}
	}
}
