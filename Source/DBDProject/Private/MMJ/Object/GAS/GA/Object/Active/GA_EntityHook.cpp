// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/GA/Object/Active/GA_EntityHook.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "JMS/GAS/SurvivorAttributeSet.h"
#include "MMJ/Object/Component/IC_Hook.h"
#include "MMJ/Object/Interactable/DBDObject.h"
#include "MMJ/Object/Interactable/Obj_Entity.h"
#include "MMJ/Object/Interactable/Obj_Hook.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/GAS/DBDAbilitySystemComponent.h"

UGA_EntityHook::UGA_EntityHook()
{
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::OwnedTagPresent;
	TriggerData.TriggerTag = DBDGameplayTags::Object_Status_IsActive;
	AbilityTriggers.Add(TriggerData);
}

void UGA_EntityHook::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// 1. Hook에 걸려있는 CapturedActor를 가져와서 HookHP에 델리게이트 함수 바인딩
	if (AObj_Entity* Entity = Cast<AObj_Entity>(OwningObject))
	{
		Entity->SetActive();

		if (Entity->OwnerObjIC)
		{
			Hook = Cast<AObj_Hook>(Entity->OwnerObject);
			HookIC = Cast<UIC_Hook>(Entity->OwnerObjIC);
			if (HookIC)
			{
				if (ADBDCharacter* Survivor = Cast<ADBDCharacter>(HookIC->GetCapturedActor()))
				{
					CachedCapturedActor = Survivor;
					if (UAbilitySystemComponent* ASC = Survivor->GetAbilitySystemComponent())
					{
						MaxHookHP = ASC->GetNumericAttribute(USurvivorAttributeSet::GetMaxHookHPAttribute());
						CapturedActorHPDelegateHandle = ASC->GetGameplayAttributeValueChangeDelegate(USurvivorAttributeSet::GetHookHPAttribute()).AddUObject(this, &ThisClass::OnCapturedActorHealthUpdated);
						//ASC->GetGameplayAttributeValueChangeDelegate(USurvivorAttributeSet::GetHookHPAttribute()).Remove(CapturedActorHPDelegateHandle);
					}
				}
			}
		}
	}


	// 생존자가 구출할 경우
	UAbilityTask_WaitGameplayEvent* RescueTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this,
		DBDGameplayTags::Object_Event_Interact);
	RescueTask->EventReceived.AddDynamic(this, &ThisClass::ExecuteTaskByEvent);
	RescueTask->ReadyForActivation();
	
}

void UGA_EntityHook::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{

	if (IsValid(CachedCapturedActor.Get()) && CapturedActorHPDelegateHandle.IsValid())
	{
		if (ADBDCharacter* Survivor = Cast<ADBDCharacter>(CachedCapturedActor.Get()))
		{
			if (UAbilitySystemComponent* ASC = Survivor->GetAbilitySystemComponent())
			{
				ASC->GetGameplayAttributeValueChangeDelegate(USurvivorAttributeSet::GetHookHPAttribute()).Remove(CapturedActorHPDelegateHandle);
			}
		}
	}
	if (AObj_Entity* Entity = Cast<AObj_Entity>(OwningObject))
	{
		Entity->SetInActive();
	}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_EntityHook::OnCompleteAbility()
{
	if (HookIC)
	{
		if (HookPhase == EHookPhase::Phase_Final)
		{
			HookIC->DestroyInteraction(CachedCapturedActor.Get());
		}
		else
		{
			HookIC->FinishInteraction(CachedCapturedActor.Get());
		}
	}
}

void UGA_EntityHook::OnCapturedActorHealthUpdated(const FOnAttributeChangeData& OnAttributeChangeData)
{
	if (!MaxHookHP) return;
	
	HookHP = OnAttributeChangeData.NewValue;

	DissolvePercent = HookHP / MaxHookHP;
	if (AObj_Entity* Entity = Cast<AObj_Entity>(OwningObject))
	{
		float NewDissolvePercent = 2 - (HookHP / MaxHookHP) * 2;
		//float DissolveAmount = FMath::FInterpTo(CachedDissolvePercent, DissolvePercent, 0.1f, 0.1f);
		Entity->SetDissolve(NewDissolvePercent);

		CachedDissolvePercent = DissolvePercent;
	}
	
	if (DissolvePercent > 0.01f && DissolvePercent <= 0.5f)
	{
		if (HookPhase != EHookPhase::Phase_Entity)
		{
			HookPhase = EHookPhase::Phase_Entity;

			// UAbilityTask_PlayMontageAndWait* EntityStartTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			// 	this,
			// 	"EntityStartTask",
			// 	EntityMontage_EntityStart);
			// EntityStartTask->OnBlendOut.AddDynamic(this, &ThisClass::OnPhaseEntity);
			// EntityStartTask->ReadyForActivation();
			OnPhaseEntity();
		}
	}
	else if (DissolvePercent <= 0.01f)
	{
		// 사망
		if (HookPhase != EHookPhase::Phase_Final)
		{
			HookPhase = EHookPhase::Phase_Final;
			Hook->SetHookPhase(HookPhase);

			OnPhaseFinal();
		}
	}
	else
	{
		if (HookPhase != EHookPhase::Phase_Normal)
		{
			HookPhase = EHookPhase::Phase_Normal;
			Hook->SetHookPhase(HookPhase);
		}
	}
	
}

void UGA_EntityHook::OnPhaseNormal()
{
}

void UGA_EntityHook::OnPhaseEntity()
{
	// 2페이즈
	// 처음 갈고리에 걸린 생존자의 체력이 50% 이하로 떨어짐
	// 한 번 갈고리에 걸렸으나 잠식되지 않은 생존자가 다시 갈고리에 걸림
	Hook->SetHookPhase(HookPhase);
	OnInteractWithHook(DBDGameplayTags::Object_Progress_OnProgress);
	UAbilityTask_PlayMontageAndWait* StruggleTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
				this,
				"StruggleTask",
				EntityMontage_Entity);
	StruggleTask->ReadyForActivation();

	// 스킬체크 감지(엔티티의 공격)
	UAbilityTask_WaitGameplayEvent* Task = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this,
		DBDGameplayTags::Object_Event_Check
		);
	Task->EventReceived.AddDynamic(this, &ThisClass::ExecuteTaskByEvent);
	Task->ReadyForActivation();
}

void UGA_EntityHook::OnPhaseFinal()
{
	// 3페이즈 (사망)
	// 갈고리에 걸린 뒤 체력이 0%까지 떨어졌거나, 이미 잠식된 상태에서 갈고리에 걸림
	// 유일하게 살아남은 상태에서 갈고리에 걸림
	// 살아있는 모든 생존자가 갈고리에 걸린 상태에서 잠식 단계에 진입
	OnInteractWithHook(DBDGameplayTags::Object_Progress_Complete);
	
	UAbilityTask_PlayMontageAndWait* FinalTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
				this,
				"FinalTask",
				EntityMontage_Final);
	FinalTask->OnBlendOut.AddDynamic(this, &ThisClass::OnCompleteAbility);
	FinalTask->ReadyForActivation();

}

void UGA_EntityHook::OnInteractWithHook(FGameplayTag EventTag)
{
	FGameplayEventData Data;
	Data.EventTag = EventTag;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Hook, DBDGameplayTags::Object_Event_Interact, Data);
}

// EventData에 따라 몽타주&로직 다르게 실행
void UGA_EntityHook::ExecuteTaskByEvent(FGameplayEventData Data)
{
	Super::ExecuteTaskByEvent(Data);

	// 스킬체크 실패했을 때
	if (Data.InstigatorTags.HasTag(DBDGameplayTags::Object_Event_Result_Failure))
	{
		CurrentActorInfo->AbilitySystemComponent->CurrentMontageJumpToSection("Fail");

		// 스킬체크 실패하면 엔티티가 실제 공격하는 시점에 맞춰 Effect적용할 Task
		UAbilityTask_WaitGameplayEvent* EffectTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
			this,
			DBDGameplayTags::Object_Event_Check);
		EffectTask->EventReceived.AddDynamic(this, &ThisClass::ExecuteGameplayEffectAndCue);
		EffectTask->ReadyForActivation();
	}

	// 생존자가 구출했을 때
	if (Data.EventTag == DBDGameplayTags::Object_Event_Interact)
	{
		OnCompleteAbility();
	}
}

void UGA_EntityHook::ExecuteGameplayEffectAndCue(FGameplayEventData Data)
{
	if (!CachedCapturedActor.IsValid()) return;
	
	if (Data.InstigatorTags.HasTag(DBDGameplayTags::Object_Event_Result_Failure))
	{
		if (UAbilitySystemComponent* Target = CachedCapturedActor->GetAbilitySystemComponent())
		{
			if (!OwningObjectASC->GetObjDataAsset()->SkillCheckFailureEffects.IsEmpty())
			{
				for (const FObjGEStruct GE : OwningObjectASC->GetObjDataAsset()->SkillCheckFailureEffects)
				{
					FGameplayEffectSpecHandle SpecHandle = OwningObjectASC->MakeOutgoingSpec(
						GE.GameplayEffect, 1, OwningObjectASC->MakeEffectContext());
					OwningObjectASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), Target);
				}
			}
		}
	}
}
