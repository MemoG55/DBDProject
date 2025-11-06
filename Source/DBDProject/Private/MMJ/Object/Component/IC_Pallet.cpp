// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Component/IC_Pallet.h"

#include "MMJ/Object/Interactable/Obj_Pallet.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"

UIC_Pallet::UIC_Pallet()
{
	ActivationBlockTags.RemoveTag(DBDGameplayTags::Object_Status_IsComplete);
	ActivationBlockTags.AddTag(DBDGameplayTags::Object_Status_IsDestroy);

	SurvivorActivationBlockTags.AddTag(DBDGameplayTags::Object_Status_IsComplete);
}

void UIC_Pallet::StartInteraction(AActor* Actor)
{
	if (UDBDBlueprintFunctionLibrary::IsKiller(Actor))
	{
		DestroyInteraction(Actor);
	}
	else
	{
		Super::StartInteraction(Actor);
	}
}

void UIC_Pallet::FinishInteraction(AActor* Actor)
{
	Super::FinishInteraction(Actor);

	CompleteInteraction(Actor);
}

void UIC_Pallet::CompleteInteraction(AActor* Actor)
{
	Super::CompleteInteraction(Actor);
}

void UIC_Pallet::DestroyInteraction(AActor* Actor)
{
	Super::DestroyInteraction(Actor);
	
	OwningObjectASC->ExecuteGameplayCue(DBDGameplayTags::Interactable_Object_Pallet);
	if (OwningObjectASC->GetObjDataAsset() && OwningObjectASC->GetObjDataAsset()->CompleteEffect)
	{
		OwningObjectASC->RemoveActiveGameplayEffectBySourceEffect(OwningObjectASC->GetObjDataAsset()->CompleteEffect, OwningObjectASC);
	}

	if (OwningObjectASC->GetObjDataAsset() && OwningObjectASC->GetObjDataAsset()->ActivateEffect)
	{
		OwningObjectASC->RemoveActiveGameplayEffectBySourceEffect(OwningObjectASC->GetObjDataAsset()->ActivateEffect, OwningObjectASC);
	}
}

void UIC_Pallet::SetInteractors(AActor* Actor)
{
	Super::SetInteractors(Actor);

	CachedCurrentInteractor = Actor;
}

void UIC_Pallet::UnSetInteractors(AActor* Actor)
{
	Super::UnSetInteractors(Actor);

	CachedCurrentInteractor = nullptr;
}
