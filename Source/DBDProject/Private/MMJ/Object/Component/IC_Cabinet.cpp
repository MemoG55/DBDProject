// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Component/IC_Cabinet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "MMJ/Object/Interactable/Obj_Cabinet.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"

UIC_Cabinet::UIC_Cabinet()
{
	bIsInteractorLocationSet = true;
}

void UIC_Cabinet::Capture(AActor* Actor)
{
	if (IsValid(Actor))
	{
		CapturedActor = Actor;
	}
	else
	{
		CapturedActor = nullptr;
	}
}

void UIC_Cabinet::StartInteraction(AActor* Actor)
{
	Super::StartInteraction(Actor);

	// IsActive태그가 붙어있으면 발동이 안되는 것을 고려해 Ability에 Gameplay Event로 트리거를 설정함
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwningObject, DBDGameplayTags::Object_Status_IsActive, FGameplayEventData());
}

void UIC_Cabinet::FinishInteraction(AActor* Actor)
{
	if (!IsValid(GetCapturedActor()))
	{
		bIsActiveWhenInteractorsEmpty = false;
	}

	// TODO::
	// 살인마가 투척 장전을 완료했을 경우 사용했던 투척무기를 제자리로 돌려놓음
	if (UDBDBlueprintFunctionLibrary::IsKiller(Actor) && UDBDBlueprintFunctionLibrary::NativeActorHasTag(Actor, DBDGameplayTags::Killer_Huntress_Status_AxeFull))
	{
		if (AObj_Cabinet* Cabinet = Cast<AObj_Cabinet>(OwningObject))
		{
			if (Cabinet->GetCombinedActor() && !Cabinet->GetCombinedActor()->IsAttachedTo(Cabinet))
			{
				Cabinet->GetCombinedActor()->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
				Cabinet->GetCombinedActor()->AttachToActor(Cabinet, FAttachmentTransformRules::KeepRelativeTransform, "ProjectileAttachSocket");
			}
		} 
	}
	
	Super::FinishInteraction(Actor);

	bIsActiveWhenInteractorsEmpty = true;
}


void UIC_Cabinet::SetInteractors(AActor* Actor)
{
	Super::SetInteractors(Actor);

	CachedCurrentInteractor = Actor;
}

void UIC_Cabinet::UnSetInteractors(AActor* Actor)
{
	Super::UnSetInteractors(Actor);

	CachedCurrentInteractor = nullptr;
}

bool UIC_Cabinet::CanInteraction(AActor* Actor)
{
	return Super::CanInteraction(Actor);
}
