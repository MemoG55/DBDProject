// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/TestSurvivor.h"

#include "AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MMJ/Object/DBDObject.h"
#include "MMJ/Object/GAS/ObjAbilitySystemComponent.h"
#include "MMJ/Object/GAS/GE/ObjGE_Active.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDGameplayTags.h"

void ATestSurvivor::TryInteract()
{
	TArray<AActor*> AllActors;
	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::SphereTraceMulti(GetWorld(), GetActorLocation(), GetActorLocation(), 150.f,
		ETraceTypeQuery::TraceTypeQuery1, false, AllActors, EDrawDebugTrace::Type::ForDuration, HitResults, true);

	TSet<AActor*> UniqueActors;
	for (const FHitResult& HitResult : HitResults)
	{
		if (ADBDObject* Obj = Cast<ADBDObject>(HitResult.GetActor()))
		{
			UniqueActors.Add(Obj);
		}		
	}

	for (AActor* Actor : UniqueActors)
	{
		if (ADBDObject* Obj = Cast<ADBDObject>(Actor))
		{
			Interact_Object(Obj);
		}		
	}
}

void ATestSurvivor::CancelInteract()
{
	//CachedCurrentInteractObject->OnDisconnect.AddUObject()
}

void ATestSurvivor::SkillCheck()
{
}

void ATestSurvivor::Interact_Object_Implementation(ADBDObject* Object)
{
	if (IsValid(Object))
	{
		if (UAbilitySystemComponent* ASC = Object->GetAbilitySystemComponent())
		{
			if (Object->CanInteraction(this))
			{
				CachedCurrentInteractObject = Object;
				Object->Execute_Interaction(Object, this);

				
				// 태그부여 활성화 (발전기 -> 수리작업, 탈출구 -> 개방, 갈고리 -> 엔티티, 캐비닛 -> 숨기;애니메이션만, 상자 -> 열고 아이템, 판자 -> 부수기/넘어가기/쓰러트리기)
				if (!UDBDBlueprintFunctionLibrary::NativeActorHasTag(Object, DBDGameplayTags::Object_Status_IsActive))
				{
					// 1. 단순 태그만 부여하는 방식
					//ASC->AddLooseGameplayTag(DBDGameplayTags::Object_Status_IsActive);
					
					// 2. GE를 넘기는 방식
					//FGameplayEffectContextHandle SpecHandle = ASC->MakeEffectContext();
					//FGameplayEffectSpecHandle Spec = ASC->MakeOutgoingSpec(UObjGE_Active::StaticClass(), 1, SpecHandle);
					//ASC->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
				}
			}
			//CachedCurrentInteractObject = nullptr;
			//Object->EndInteraction(this);
			//ASC->RemoveLooseGameplayTag(DBDGameplayTags::Object_Status_IsActive);
		}
	}
}

