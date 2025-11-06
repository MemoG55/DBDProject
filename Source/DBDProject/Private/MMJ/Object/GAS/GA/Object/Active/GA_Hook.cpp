// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/GA/Object/Active/GA_Hook.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "MMJ/Object/Component/ICObject.h"
#include "MMJ/Object/DataAsset/ObjDataAsset.h"
#include "MMJ/Object/GAS/ObjAbilitySystemComponent.h"
#include "MMJ/Object/GAS/GE/ObjGE_HookHp.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Character/DBDCharacter.h"

UGA_Hook::UGA_Hook()
{
}

void UGA_Hook::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// TODO :: 들어가야 할 것.
	// 1. Active되면 즉시 재생될 몽타주 (Loop는 AnimBP에서 처리)
	// 2. 구출 시 몽타주 o
	// 3. 자력탈출 시 몽타주 o
	// 4. 갈고리에 걸린 생존자가 희생될 경우 엔티티몽타주 재생 후 완료처리 받아야함
	//    - ActiveGA가 아닌 DestroyGA로 바로 넘어가기

	if (IsValid(Montage_Start))
	{
		ObjectPlayMontage(Montage_Start);
	}

	// 걸린 생존자의 HP를 깎는 ActivateAdditionalEffect 적용
	if (OwningObjectASC->GetObjDataAsset()&& !OwningObjectASC->GetObjDataAsset()->ActiveAdditionalEffects.IsEmpty())
	{
		if (ADBDCharacter* Survivor = Cast<ADBDCharacter>(ObjInteractableComponent->GetCapturedActor()))
		{
			CachedCapturedActor = Survivor;
			UAbilitySystemComponent* TargetASC = CachedCapturedActor->GetAbilitySystemComponent();
			FGameplayEffectContextHandle SpecHandle = OwningObjectASC->MakeEffectContext();
				
			FGameplayEffectSpecHandle Spec = OwningObjectASC->MakeOutgoingSpec(UObjGE_HookHp::StaticClass(), 1, SpecHandle);
			float Hp = 100.f;
			if (TargetASC->GetGameplayTagCount(DBDGameplayTags::Survivor_Status_HookCount) == 2)
			{
				Hp = 50.f;
			}
			else if (TargetASC->GetGameplayTagCount(DBDGameplayTags::Survivor_Status_HookCount) >= 3)
			{
				Hp = 1.f;
			}
			Spec.Data->SetSetByCallerMagnitude(DBDGameplayTags::Object_Progress_OnProgress, Hp);
			OwningObjectASC->ApplyGameplayEffectSpecToTarget(*Spec.Data.Get(), TargetASC);
			
			for (const FObjGEStruct GEStruct : OwningObjectASC->GetObjDataAsset()->ActiveAdditionalEffects)
			{
				FGameplayEffectSpecHandle GESpec = OwningObjectASC->MakeOutgoingSpec(GEStruct.GameplayEffect, 1, SpecHandle);
				OwningObjectASC->ApplyGameplayEffectSpecToTarget(*GESpec.Data.Get(), TargetASC);
			}	
		}
	}

	WaitTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this,
		DBDGameplayTags::Object_Event_Interact
	);
	WaitTask->EventReceived.AddDynamic(this, &ThisClass::Escaped);
	WaitTask->ReadyForActivation();
}

void UGA_Hook::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (OwningObjectASC->GetObjDataAsset()&& !OwningObjectASC->GetObjDataAsset()->ActiveAdditionalEffects.IsEmpty())
	{
		//KMJ_1027_Add for Valid Check
		if (CachedCapturedActor.IsValid())
		{
			UAbilitySystemComponent* TargetASC = Cast<UAbilitySystemComponent>(CachedCapturedActor->GetAbilitySystemComponent());
			for (const FObjGEStruct GEStruct : OwningObjectASC->GetObjDataAsset()->ActiveAdditionalEffects)
			{
				TargetASC->RemoveActiveGameplayEffectBySourceEffect(GEStruct.GameplayEffect, OwningObjectASC);
			}
		}
	}
}

void UGA_Hook::Escaped(FGameplayEventData Data)
{
	if (Data.EventTag.MatchesTag(DBDGameplayTags::Object_Event_Interact))
	{
		if (Data.InstigatorTags.HasTag(DBDGameplayTags::Survivor_Status_Escaped))
		{
			TaskMontage = Montage_Escape;
		}
		else
		{
			TaskMontage = Montage_Escape;
		}
	}
	else
	{
		if (Data.EventTag.MatchesTag(DBDGameplayTags::Object_Progress_Complete))
		{
			TaskMontage = Montage_Finish;
		}
		else if (Data.EventTag.MatchesTag(DBDGameplayTags::Object_Progress_OnProgress))
		{
			TaskMontage = Montage_EntityStart;
		}
	}
	ObjectPlayMontage(TaskMontage);
	// UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
	// 	this,
	// 	"MontageTask",
	// 	TaskMontage);
	// MontageTask->ReadyForActivation();
}
