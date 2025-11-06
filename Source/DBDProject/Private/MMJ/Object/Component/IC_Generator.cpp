// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Component/IC_Generator.h"

#include "MMJ/Object/Component/IC_Entity.h"
#include "MMJ/Object/Interactable/Obj_Entity.h"
#include "MMJ/Object/Interactable/Obj_Generator.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"

UIC_Generator::UIC_Generator()
{
	bIsInteractorLocationSet = true;

	KillerActivationBlockTags.AddTag(DBDGameplayTags::Object_Status_IsDestroy);
}

void UIC_Generator::StartInteraction(AActor* Actor)
{

	// Actor가 살인마인지, 생존자인지 판별하는 로직
	if (UDBDBlueprintFunctionLibrary::IsKiller(Actor))
	{
		if (!UDBDBlueprintFunctionLibrary::NativeActorHasTag(OwningObject, DBDGameplayTags::Object_Status_IsDestroy))
		{
			DestroyInteraction(Actor);
		}
	}
	else if (UDBDBlueprintFunctionLibrary::IsSurvivor(Actor))
	{
		Super::StartInteraction(Actor);
	}
}

void UIC_Generator::CompleteInteraction(AActor* Actor)
{
	Super::CompleteInteraction(Actor);
	
	if (AObj_Entity* Entity = OwningObject->GetEntity())
	{
		Entity->SetActive();
		if (UIC_Entity* EntityIC = Cast<UIC_Entity>(Entity->GetInteractableComponent()))
		{
			if (EntityIC->IsActivate())
			{
				return;
			}
	
			EntityIC->StartInteraction(OwningActor);
		}
	}
	
}

bool UIC_Generator::CanInteraction(AActor* Actor)
{
	if (!Super::CanInteraction(Actor))
	{
		return false;
	}
	
	// 상호작용이 가능한 경우
	// 1. 현재 상호작용중인 인원 수가 총 인원보다 적을 때
	if (UDBDBlueprintFunctionLibrary::IsSurvivor(Actor))
	{
		if ( MaxInteractorCount <= GetInteractors().Num())
		{
			return false;
		}
	}
	
	return true;
}

