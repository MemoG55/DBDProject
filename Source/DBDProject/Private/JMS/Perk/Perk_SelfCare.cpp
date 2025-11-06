// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Perk/Perk_SelfCare.h"

#include "AbilitySystemComponent.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/GAS/GA/Interaction/GA_SelfCare.h"
#include "Shared/Character/DBDCharacter.h"


UPerk_SelfCare::UPerk_SelfCare()
{
	PerkID = FName(TEXT("SelfCare"));
}

void UPerk_SelfCare::OnServerSideInitialized()
{
	Super::OnServerSideInitialized();
	ADBDCharacter* DBDCharacter = Cast<ADBDCharacter>(GetOuterAsDBDCharacter());
	UAbilitySystemComponent* ASC = DBDCharacter->GetAbilitySystemComponent();
	FGameplayAbilitySpec Spec = FGameplayAbilitySpec(SelfCareAbility, 1,
	                                                 (int32)ESurvivorAbilityInputID::SelfCare, GetOuterAsDBDCharacter());

	ASC->GiveAbility(Spec);
}
