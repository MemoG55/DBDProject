// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/GA/Object/Active/GA_Cabinet.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "MMJ/Object/Component/IC_Cabinet.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"

UGA_Cabinet::UGA_Cabinet()
{
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	TriggerData.TriggerTag = DBDGameplayTags::Object_Status_IsActive;
	AbilityTriggers.Add(TriggerData);
}

void UGA_Cabinet::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// 캐비닛이 현재 재생중인 몽타주가 있다면 바로 End처리  ** 오브젝트는 Client가 존재하지 않아서 WaitGameplayEvent로 몽타주 실행이 안되기 때문
	if (OwningObject->GetSkeletalMeshComponent()->GetAnimInstance()->IsAnyMontagePlaying())
	{
		K2_EndAbility();
		return;
	}

	// Capture 인터페이스함수 사용을 위한 캐스팅
	IC_Cabinet = Cast<UIC_Cabinet>(ObjInteractableComponent);
	CapturedActor = IC_Cabinet->GetCapturedActor();

	// 살인마 로직
	if (UDBDBlueprintFunctionLibrary::IsKiller(ObjInteractableComponent->CachedCurrentInteractor))
	{
		// 생존자가 있다면 꺼낸 후 CapturedActor를 Null값으로 
		if (IsValid(CapturedActor))
		{
			TaskMontage = Montage_KillerFindSurvivor;
			IC_Cabinet->Capture(nullptr);
		}
		else
		{
			// TODO :: if 투척을 필요로하는 살인마 + 재장전 필요한지? 조건 필요 
			if (!UDBDBlueprintFunctionLibrary::NativeActorHasTag(ObjInteractableComponent->CachedCurrentInteractor, DBDGameplayTags::Killer_Huntress_Status_AxeFull))
			{
				TaskMontage = Montage_KillerOpenReload;
			}
			else
			{
				TaskMontage = Montage_KillerOpenEmpty;
			}
		}
	}
	// 생존자 로직
	else
	{
		if (IsValid(CapturedActor))
		{
			// 현재 상호작용중인 액터가 CapturedActor(숨은액터)일 경우 나가는 몽타주
			if (CapturedActor == ObjInteractableComponent->CachedCurrentInteractor)
			{
				TaskMontage = Montage_SurvivorOpenExit;
				// 나가기 처리
				IC_Cabinet->Capture(nullptr);
			}
			// 아니라면 다른 생존자가 상호작용인 것이기 때문에 Block
			else
			{
				TaskMontage = Montage_SurvivorOpenExist;
			}
		}
		else
		{
			TaskMontage = Montage_SurvivorOpenHide;
			// 현재 상호작용중인 액터를 숨은 액터로 Capture
			IC_Cabinet->Capture(ObjInteractableComponent->CachedCurrentInteractor);
		}
	}

	ObjectPlayMontage();
	K2_EndAbility();
}
