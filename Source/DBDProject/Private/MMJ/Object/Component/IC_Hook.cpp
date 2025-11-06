// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Component/IC_Hook.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/GAS/SurvivorAttributeSet.h"
#include "KMJ/Character/KillerCharacter.h"
#include "MMJ/Object/Component/IC_Entity.h"
#include "MMJ/Object/GAS/GE/ObjGE_HookHp.h"
#include "MMJ/Object/Interactable/Obj_Entity.h"
#include "MMJ/Object/Interactable/Obj_Hook.h"
#include "Net/UnrealNetwork.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDDebugHelper.h"

UIC_Hook::UIC_Hook()
{
	KillerActivationBlockTags.AddTag(DBDGameplayTags::Object_Status_IsActive);
}

void UIC_Hook::Capture(AActor* Actor)
{
	if (IsValid(Actor))
	{
		CapturedActor = Actor;
		SetInteractors(CapturedActor);
	}
	else
	{
		if (IsValid(CapturedActor))
		{
			UnSetInteractors(CapturedActor);
		}
		CapturedActor = nullptr;
	}
}

void UIC_Hook::StartInteraction(AActor* Actor)
{

	// 살인마가 생존자를 건다
	if (UDBDBlueprintFunctionLibrary::IsKiller(Actor))
	{
		if (AKillerCharacter* Killer = Cast<AKillerCharacter>(Actor))
		{
			Capture(Killer->GetCarriedSurvivorCharacter());
		}
		
		if (!CapturedActor) return;
		
		if (ASurvivorCharacter* HookedSurvivorCharacter = Cast<ASurvivorCharacter>(CapturedActor))
		{
			HookedSurvivorCharacter->AuthHookSurvivor(Hook);
		}
		Super::StartInteraction(Actor);

		if (AObj_Entity* Entity = OwningObject->GetEntity())
		{
			Entity->SetActive();
			if (UIC_Entity* EntityIC = Cast<UIC_Entity>(Entity->GetInteractableComponent()))
			{
				if (EntityIC->IsActivate())
				{
					return;
				}

				EntityIC->StartInteraction(CapturedActor);
			}
		}
		
		
	}
	// 생존자는 다른 생존자가 걸려있으면 구출하고, 아니면 파괴한다
	else if (UDBDBlueprintFunctionLibrary::IsSurvivor(Actor))
	{
		if (!CheckAuthority()) return;
		
		// 생존자가 걸려있으면 IsActive가 있고 구출이 가능
		if (IsActivate() && CapturedActor)
		{
			//FinishInteraction(Actor);
		}
		// 아니라면 IsActive태그가 없다. 파괴가능
		else
		{
			// TODO :: 파괴도 무슨 퍽이 있어야 가능하다던데 이건 어떻게 할지?
			DestroyInteraction(Actor);
		}
	}
}

void UIC_Hook::TickInteraction(AActor* Actor)
{
	Super::TickInteraction(Actor);
	if (!CapturedActor) return;

}

void UIC_Hook::FinishInteraction(AActor* Actor)
{
	if (UDBDBlueprintFunctionLibrary::IsKiller(Actor))
	{
		Super::FinishInteraction(Actor);
	}
	else
	{
		if (ASurvivorCharacter* CapturedSurvivor = Cast<ASurvivorCharacter>(CapturedActor))
		{
			CapturedSurvivor->SetSurvivorInjured();
		}

		if (AObj_Entity* Entity = OwningObject->GetEntity())
		{
			//UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Entity, DBDGameplayTags::Object_Event_Interact, FGameplayEventData());
		}
		
		// 생존자의 구출 또는 희생
		
		if (AObj_Entity* Entity = OwningObject->GetEntity())
		{
			Entity->SetInActive();
			if (UIC_Entity* EntityIC = Cast<UIC_Entity>(Entity->GetInteractableComponent()))
			{
				EntityIC->FinishInteraction(CapturedActor);
			}
		}
		Capture(nullptr);

		Super::FinishInteraction(Actor);
		
	}

}

void UIC_Hook::BeginPlay()
{
	Super::BeginPlay();

	if (OwningObject)
	{
		if (AObj_Hook* ObjectHook = Cast<AObj_Hook>(OwningObject))
		{
			Hook = ObjectHook;
		}
	}
}


void UIC_Hook::DestroyInteraction(AActor* Actor)
{
	Super::DestroyInteraction(Actor);

	if (OwningObjectASC->GetObjDataAsset() && OwningObjectASC->GetObjDataAsset()->ActivateEffect)
	{
		if (OwningGameplayEffectCDO.IsValid())
		{
			OwningObjectASC->RemoveActiveGameplayEffect(OwningGameplayEffectCDO);
			OwningGameplayEffectCDO.Invalidate();
		}
	}
	
	if (AObj_Entity* Entity = OwningObject->GetEntity())
	{
		Entity->SetInActive();
		if (UIC_Entity* EntityIC = Cast<UIC_Entity>(Entity->GetInteractableComponent()))
		{
			EntityIC->FinishInteraction(Actor);
		}
	}
}

bool UIC_Hook::CanInteraction(AActor* Actor)
{
	if (!Super::CanInteraction(Actor)) return false;
	
	if (UDBDBlueprintFunctionLibrary::IsKiller(Actor))
	{
		// 살인마가 생존자를 업었을때 판별 로직
		if (AKillerCharacter* Killer = Cast<AKillerCharacter>(Actor))
		{
			if (Killer->GetCarriedSurvivorCharacter() == nullptr)
			{
				return false;
			}
			return true;
		}
	}
	else
	{
		// TODO :: 프로토타입에서는 바로 사망처리 한 뒤 추후 고도화 때 구출 시스템 다시 구현
		if (!IsActivate() && false)
		{
			return false;
		}
	}

	return true;
}
