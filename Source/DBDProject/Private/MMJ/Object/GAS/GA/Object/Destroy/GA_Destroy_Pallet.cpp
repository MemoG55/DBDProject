// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/GA/Object/Destroy/GA_Destroy_Pallet.h"

#include "MMJ/Object/Interactable/DBDObject.h"

void UGA_Destroy_Pallet::ExecuteGameplayEffectAndCue(FGameplayEventData Data)
{
	Super::ExecuteGameplayEffectAndCue(Data);

	OwningObject->SetDestroyed();
}
