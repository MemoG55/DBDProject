// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Component/ICHook.h"

#include "JMS/GAS/SurvivorAttributeSet.h"
#include "KMJ/Character/KillerCharacter.h"
#include "MMJ/Object/TestSurvivor.h"
#include "MMJ/Object/GAS/GE/ObjGE_HookHp.h"
#include "MMJ/Object/Interactable/Obj_Hook.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/Character/DBDCharacter.h"

UICHook::UICHook()
{
	KillerActivationBlockTags.AddTag(DBDGameplayTags::Object_Status_IsActive);
}

void UICHook::StartInteraction(AActor* Actor)
{

	// 살인마가 생존자를 건다
	if (UDBDBlueprintFunctionLibrary::IsKiller(Actor))
	{
		if (AKillerCharacter* Killer = Cast<AKillerCharacter>(Actor))
		{
			SetHookedSurvivor(Killer->GetCarriedSurvivorCharacter());
		}
		
		if (!HookedSurvivor || !HookedSurvivor->GetAbilitySystemComponent()) return;

		SetInteractors(HookedSurvivor);
		ASurvivorCharacter* HookedSurvivorCharacter = Cast<ASurvivorCharacter>(HookedSurvivor);
		if (HookedSurvivorCharacter)
		{
			HookedSurvivorCharacter->HookSurvivor(Hook);
		}
		Super::StartInteraction(Actor);
		
		// 걸린 생존자의 HealthUpdate델리게이트에 함수 연결
		SetTaskAttribute(USurvivorAttributeSet::GetHookHPAttribute());
		
		// 걸린 생존자의 HP를 깎는 ActivateAdditionalEffect 적용
		if (OwningObjectASC->GetObjDataAsset()&& !OwningObjectASC->GetObjDataAsset()->ActiveAdditionalEffects.IsEmpty())
		{
			UAbilitySystemComponent* TargetASC = HookedSurvivor->GetAbilitySystemComponent();
			for (const FObjGEStruct GEStruct : OwningObjectASC->GetObjDataAsset()->ActiveAdditionalEffects)
			{
				FGameplayEffectContextHandle SpecHandle = OwningObjectASC->MakeEffectContext();
				FGameplayEffectSpecHandle Spec = OwningObjectASC->MakeOutgoingSpec(GEStruct.GameplayEffect, 1, SpecHandle);
				OwningObjectASC->ApplyGameplayEffectSpecToTarget(*Spec.Data.Get(), TargetASC);
			}

			if (TargetASC->GetGameplayTagCount(DBDGameplayTags::Survivor_Status_HookCount) == 2)
			{
				FGameplayEffectContextHandle SpecHandle = OwningObjectASC->MakeEffectContext();
				FGameplayEffectSpecHandle Spec = OwningObjectASC->MakeOutgoingSpec(UObjGE_HookHp::StaticClass(), 1, SpecHandle);
				Spec.Data->SetSetByCallerMagnitude(DBDGameplayTags::Object_Progress_OnProgress, 50.f);
				OwningObjectASC->ApplyGameplayEffectSpecToTarget(*Spec.Data.Get(), TargetASC);
			}
			else if (TargetASC->GetGameplayTagCount(DBDGameplayTags::Survivor_Status_HookCount) >= 3)
			{
				FGameplayEffectContextHandle SpecHandle = OwningObjectASC->MakeEffectContext();
				FGameplayEffectSpecHandle Spec = OwningObjectASC->MakeOutgoingSpec(UObjGE_HookHp::StaticClass(), 1, SpecHandle);
				Spec.Data->SetSetByCallerMagnitude(DBDGameplayTags::Object_Progress_OnProgress, 1.f);
				OwningObjectASC->ApplyGameplayEffectSpecToTarget(*Spec.Data.Get(), TargetASC);
			}
		}
	}
	// 생존자는 다른 생존자가 걸려있으면 구출하고, 아니면 파괴한다
	else if (UDBDBlueprintFunctionLibrary::IsSurvivor(Actor))
	{
		if (!CheckAuthority()) return;
		
		// 생존자가 걸려있으면 IsActive가 있고 구출이 가능
		if (UDBDBlueprintFunctionLibrary::NativeActorHasTag(OwningActor, DBDGameplayTags::Object_Status_IsActive) && HookedSurvivor)
		{
			if (OwningObjectASC->GetObjDataAsset()&& !OwningObjectASC->GetObjDataAsset()->ActiveAdditionalEffects.IsEmpty())
			{
				if (UDBDAbilitySystemComponent* SurvivorASC =  Cast<UDBDAbilitySystemComponent>(HookedSurvivor->GetAbilitySystemComponent()))
				{
					for (const FObjGEStruct GEStruct : OwningObjectASC->GetObjDataAsset()->ActiveAdditionalEffects)
					{
						if (GEStruct.bRemoveWhenFinish)
						{
							SurvivorASC->RemoveActiveGameplayEffectBySourceEffect(GEStruct.GameplayEffect, OwningObjectASC);
						}
					}
				}
			}
			FinishInteraction(Actor);
		}
		// 아니라면 IsActive태그가 없다. 파괴가능
		else
		{
			// TODO :: 파괴도 무슨 퍽이 있어야 가능하다던데 이건 어떻게 할지?
			OnDestroy.Broadcast();
		}
	}
}

void UICHook::TickInteraction(AActor* Actor)
{
	Super::TickInteraction(Actor);
	if (!HookedSurvivor) return;

}

void UICHook::FinishInteraction(AActor* Actor)
{
	if (UDBDBlueprintFunctionLibrary::IsKiller(Actor))
	{
		
	}
	else
	{
		UnSetInteractors(HookedSurvivor);
		UnSetHookedSurvivor(HookedSurvivor);
		
		Super::FinishInteraction(Actor);
	}
}

void UICHook::BeginPlay()
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

bool UICHook::CanInteraction(AActor* Actor)
{
	if (!Super::CanInteraction(Actor)) return false;
	
	if (UDBDBlueprintFunctionLibrary::IsKiller(Actor))
	{
		// 살인마가 생존자를 업었을때 판별 로직
		// 살인마가 생존자를 업었다면 SetHookedSurvivor -> return true
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
		if (!UDBDBlueprintFunctionLibrary::NativeActorHasTag(OwningObject, DBDGameplayTags::Object_Status_IsActive) && false)
		{
			return false;
		}
	}

	return true;
}

void UICHook::SetHookedSurvivor(ADBDCharacter* Actor)
{
	if (!Actor) return;
	
	HookedSurvivor = Actor;
	if (UDBDAbilitySystemComponent* ASC = Cast<UDBDAbilitySystemComponent>(HookedSurvivor->GetAbilitySystemComponent()))
	{
		HookedSurvivorHPDelegateHandle = ASC->GetGameplayAttributeValueChangeDelegate(USurvivorAttributeSet::GetHookHPAttribute()).AddUObject(
		this, &ThisClass::OnSurvivorHealthUpdated);
	}
}

void UICHook::UnSetHookedSurvivor(ADBDCharacter* Actor)
{
	if (!Actor) return;
	
	if (UDBDAbilitySystemComponent* ASC = Cast<UDBDAbilitySystemComponent>(HookedSurvivor->GetAbilitySystemComponent()))
	{
		ASC->GetGameplayAttributeValueChangeDelegate(USurvivorAttributeSet::GetHookHPAttribute()).Remove(HookedSurvivorHPDelegateHandle);

		HookedSurvivor = nullptr;
	}
}

void UICHook::OnSurvivorHealthUpdated(const FOnAttributeChangeData& OnAttributeChangeData)
{
	if (OnAttributeChangeData.NewValue > 50.f)
	{
		// 탈출 가능
		if (HookPhase != EHookPhase::Phase_Normal)
		{
			HookPhase = EHookPhase::Phase_Normal;
		}
	}
	else if (OnAttributeChangeData.NewValue > 1.f)
	{
		// 엔티티 공격
		if (HookPhase != EHookPhase::Phase_Entity)
		{
			HookPhase = EHookPhase::Phase_Entity;
		}
	}
	else
	{
		// 사망
		FinishInteraction(HookedSurvivor);
		OnComplete.Broadcast();
		if (HookPhase != EHookPhase::Phase_Final)
		{
			HookPhase = EHookPhase::Phase_Final;
		}
	}
}

EHookPhase UICHook::GetHookPhase()
{
	return HookPhase;
}
