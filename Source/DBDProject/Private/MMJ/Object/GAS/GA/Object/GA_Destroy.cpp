// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/GA/Object/GA_Destroy.h"

#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "MMJ/Object/GAS/ObjAbilitySystemComponent.h"
#include "Shared/DBDGameplayTags.h"

UGA_Destroy::UGA_Destroy()
{
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::OwnedTagPresent;
	TriggerData.TriggerTag = DBDGameplayTags::Object_Status_IsDestroy;
	AbilityTriggers.Add(TriggerData);
}

void UGA_Destroy::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                  const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// 파괴 관련 몽타주 있다면 재생 (Cue에서 재생하는것 제외)
	if (IsValid(DestroyMontage))
	{
		ObjectPlayMontage(DestroyMontage);
	}
	
	if (!bAutoActive)
	{
		if (ActiveTag.IsValid())
		{
			WaitTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
				this,
				ActiveTag
				);
			WaitTask->EventReceived.AddDynamic(this, &ThisClass::ExecuteGameplayEffectAndCue);
			WaitTask->ReadyForActivation();
		}
	}
	else
	{
		ExecuteGameplayEffectAndCue(FGameplayEventData());
	}
}

void UGA_Destroy::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (IsValid(DestroyEndMontage))
	{
		ObjectPlayMontage(DestroyEndMontage);
	}
}

void UGA_Destroy::ExecuteGameplayEffectAndCue(FGameplayEventData Data)
{
	Super::ExecuteGameplayEffectAndCue(Data);
	// DestroyEffect를 제외한 추가 적용될 Effect들 적용
	if (OwningObjectASC->GetObjDataAsset() && !OwningObjectASC->GetObjDataAsset()->DestroyAdditionalEffects.IsEmpty())
	{
		for (const FObjGEStruct GEStruct : OwningObjectASC->GetObjDataAsset()->DestroyAdditionalEffects)
		{
			FGameplayEffectContextHandle SpecHandle = OwningObjectASC->MakeEffectContext();
			FGameplayEffectSpecHandle Spec = OwningObjectASC->MakeOutgoingSpec(GEStruct.GameplayEffect, 1, SpecHandle);
			OwningObjectASC->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
		}
	}
}
