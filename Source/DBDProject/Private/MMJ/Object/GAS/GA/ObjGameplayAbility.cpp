// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/GA/ObjGameplayAbility.h"

#include "MMJ/Object/Component/ICObject.h"
#include "MMJ/Object/Interactable/DBDObject.h"


UObjGameplayAbility::UObjGameplayAbility()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

UObjAbilitySystemComponent* UObjGameplayAbility::GetObjAbilitySystemComponentFromActorInfo() const
{
	return Cast<UObjAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

UAnimInstance* UObjGameplayAbility::GetAnimInstance() const
{
	if (USkeletalMeshComponent* OwningSkeletalMeshComponent = GetOwningComponentFromActorInfo())
	{
		return OwningSkeletalMeshComponent->GetAnimInstance();
	}

	return nullptr;
}

ADBDObject* UObjGameplayAbility::GetOwnerObjectFromActorInfo() const
{
	if (ADBDObject* Owner = Cast<ADBDObject>(GetOwningActorFromActorInfo()))
	{
		return Owner;
	}
	return nullptr;
}

UInteractableComponent* UObjGameplayAbility::GetInteractableComponentFromActorInfo() const
{
	if (GetOwnerObjectFromActorInfo())
	{
		return GetOwnerObjectFromActorInfo()->GetInteractableComponent();		
	}
	return nullptr;
}

void UObjGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	CheckAuthority();

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		K2_EndAbility();
		return;
	}
}

void UObjGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UObjGameplayAbility::CheckAuthority()
{
	if (!HasAuthority(&CurrentActivationInfo))
	{
		K2_EndAbility();
	}
	
	OwningObject = GetOwnerObjectFromActorInfo();
	OwningObjectASC = GetObjAbilitySystemComponentFromActorInfo();
	ObjInteractableComponent = Cast<UICObject>(GetInteractableComponentFromActorInfo());
	
	if (!IsValid(OwningObject) || !IsValid(OwningObjectASC) || !IsValid(ObjInteractableComponent))
	{
		K2_EndAbility();
	}
}

void UObjGameplayAbility::ExecuteGameplayEffectAndCue(FGameplayEventData Data)
{
	if (GameplayCueTag.IsValid())
	{
		K2_ExecuteGameplayCue(GameplayCueTag, MakeEffectContext(CurrentSpecHandle, CurrentActorInfo));
	}

	// 스킬체크 대성공 보너스
	if (Data.InstigatorTags.HasTag(DBDGameplayTags::Object_Event_Result_Success))
	{
		if (!OwningObjectASC->GetObjDataAsset()->SkillCheckSuccessEffects.IsEmpty())
		{
			for (const FObjGEStruct GE : OwningObjectASC->GetObjDataAsset()->SkillCheckSuccessEffects)
			{
				FGameplayEffectSpecHandle SpecHandle = OwningObjectASC->MakeOutgoingSpec(
					GE.GameplayEffect, 1, OwningObjectASC->MakeEffectContext());
				OwningObjectASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}

		if (OwningObjectASC->GetObjDataAsset()->SkillCheckSuccessGCTag.IsValid())
		{
			K2_ExecuteGameplayCue(OwningObjectASC->GetObjDataAsset()->SkillCheckSuccessGCTag, MakeEffectContext(CurrentSpecHandle, CurrentActorInfo));
		}
	}
	// 스킬체크 실패 페널티 (진행도 감소 + 알림 + 상호작용 불가)
	if (Data.InstigatorTags.HasTag(DBDGameplayTags::Object_Event_Result_Failure))
	{
		if (!OwningObjectASC->GetObjDataAsset()->SkillCheckFailureEffects.IsEmpty())
		{
			for (const FObjGEStruct GE : OwningObjectASC->GetObjDataAsset()->SkillCheckFailureEffects)
			{
				FGameplayEffectSpecHandle SpecHandle = OwningObjectASC->MakeOutgoingSpec(
					GE.GameplayEffect, 1, OwningObjectASC->MakeEffectContext());
				OwningObjectASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}

		if (OwningObjectASC->GetObjDataAsset()->SkillCheckFailureGCTag.IsValid())
		{
			K2_ExecuteGameplayCue(OwningObjectASC->GetObjDataAsset()->SkillCheckFailureGCTag, MakeEffectContext(CurrentSpecHandle, CurrentActorInfo));
		}
	}
	
}

void UObjGameplayAbility::ObjectPlayMontage(UAnimMontage* Montage)
{
	if (IsValid(Montage))
	{
		OwningObjectASC->PlayMontage(this, CurrentActivationInfo, Montage, 1.f);
	}
	else
	{
		if (!IsValid(TaskMontage)) return;
		
		OwningObjectASC->PlayMontage(this, CurrentActivationInfo, TaskMontage, 1.f);
	}
}

void UObjGameplayAbility::ObjectStopMontage(UAnimMontage* Montage)
{
	OwningObjectASC->CurrentMontageStop();
}
