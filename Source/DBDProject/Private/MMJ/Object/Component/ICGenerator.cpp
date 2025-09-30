// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Component/ICGenerator.h"

#include "Shared/DBDBlueprintFunctionLibrary.h"

UICGenerator::UICGenerator()
{
}

void UICGenerator::StartInteraction(AActor* Actor)
{

	// Actor가 살인마인지, 생존자인지 판별하는 로직
	if (UDBDBlueprintFunctionLibrary::IsKiller(Actor))
	{
		if (!CheckAuthority()) return;
		
		if (!UDBDBlueprintFunctionLibrary::NativeActorHasTag(OwningObject, DBDGameplayTags::Object_Status_IsDestroy))
		{
			OnDestroy.Broadcast();
		}
	}
	else if (UDBDBlueprintFunctionLibrary::IsSurvivor(Actor))
	{
		SetInteractorLocation(Actor);
		Super::StartInteraction(Actor);
	}
}

void UICGenerator::TickInteraction(AActor* Actor)
{
	Super::TickInteraction(Actor);
	
	float TaskSpeed = GetTaskAttributeOfInteractors();
	FGameplayEffectContextHandle SpecContext = OwningObjectASC->MakeEffectContext();
	SpecContext.AddSourceObject(OwningActor);
	SpecContext.AddInstigator(OwningActor, OwningActor);

	// TODO :: Effect는 별도로 지정해야 할 듯?
	FGameplayEffectSpecHandle SpecHandle = OwningObjectASC->MakeOutgoingSpec(
		OwningObjectASC->GetObjDataAsset()->ActiveAdditionalEffects[0].GameplayEffect, 1, SpecContext);
	SpecHandle.Data->SetSetByCallerMagnitude(DBDGameplayTags::Object_Progress_Speed, TaskSpeed);
	SpecHandle.Data->SetSetByCallerMagnitude(DBDGameplayTags::Object_Progress_ActorCount, GetInteractors().Num());
	OwningObjectASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void UICGenerator::UnSetInteractors(AActor* Actor)
{
	Super::UnSetInteractors(Actor);

	UnSetInteractorLocation(Actor);
}


bool UICGenerator::CanInteraction(AActor* Actor)
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

