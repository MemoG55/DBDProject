// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Perk/Perk_BotanyKnowledge.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "JMS/GAS/GE/GE_BotanyKnowledge.h"
#include "Shared/DBDDebugHelper.h"


void UPerk_BotanyKnowledge::OnInitialized()
{
	Super::OnInitialized();
	IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(GetOuterAsDBDCharacter());
	if (!ASI)
	{
		return;
	}

	UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent();
	if (!ASC)
	{
		return;
	}

	ASC->BP_ApplyGameplayEffectToSelf(UGE_BotanyKnowledge::StaticClass(), 0,
	                                    ASC->MakeEffectContext());
}
