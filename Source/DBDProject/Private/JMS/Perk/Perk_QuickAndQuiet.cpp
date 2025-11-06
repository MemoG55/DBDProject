// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Perk/Perk_QuickAndQuiet.h"

#include "AbilitySystemComponent.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "Shared/Character/DBDCharacter.h"


UPerk_QuickAndQuiet::UPerk_QuickAndQuiet()
{
	PerkID = FName(TEXT("QuickAndQuiet"));
}

void UPerk_QuickAndQuiet::OnServerSideInitialized()
{
	Super::OnServerSideInitialized();
	ASurvivorCharacter* OwnerSurvivorCharacter = Cast<ASurvivorCharacter>(GetOuterAsDBDCharacter());
	if (OwnerSurvivorCharacter)
	{
		OwnerSurvivorCharacter->OnQuickActionPlayed.AddDynamic(this, &UPerk_QuickAndQuiet::OnQuickActionPlayed);
	}
}

void UPerk_QuickAndQuiet::OnOwnerClientSideInitialized()
{
	Super::OnOwnerClientSideInitialized();
}

void UPerk_QuickAndQuiet::OnQuickActionPlayed()
{
	FGameplayEffectQuery EffectQuery;
	EffectQuery.EffectDefinition = QuickAndQuietEffect;
	int32 NumRemoved = GetOuterAsDBDCharacter()->GetAbilitySystemComponent()->RemoveActiveEffects(EffectQuery);
	if (NumRemoved > 0)
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
		                                       &UPerk_QuickAndQuiet::RestoreEffectAfterCooldown, 15.f, false);
	}
}

void UPerk_QuickAndQuiet::RestoreEffectAfterCooldown()
{
	GetOuterAsDBDCharacter()->GetAbilitySystemComponent()->BP_ApplyGameplayEffectToSelf(
		QuickAndQuietEffect, 0, GetOuterAsDBDCharacter()->GetAbilitySystemComponent()->MakeEffectContext());
}
