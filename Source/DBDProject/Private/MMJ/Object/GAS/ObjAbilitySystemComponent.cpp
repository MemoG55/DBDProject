// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/ObjAbilitySystemComponent.h"

#include "MMJ/Object/Interactable/DBDObject.h"
#include "MMJ/Object/AnimInstance/DBDObjectAnimInstance.h"
#include "MMJ/Object/DataAsset/ObjDataAsset.h"
#include "MMJ/Object/GAS/ObjAttributeSet.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Component/InteractableComponent.h"

UObjAbilitySystemComponent::UObjAbilitySystemComponent()
{


}

class ADBDObject* UObjAbilitySystemComponent::GetOwnerActorFromActorInfo()
{
	if (ADBDObject* Owner = Cast<ADBDObject>(GetAvatarActor()))
	{
		return Owner;
	}
	return nullptr;
}

void UObjAbilitySystemComponent::TaskUpdated(const FOnAttributeChangeData& OnAttributeChangeData)
{
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;

	if (IsMaxTask())
	{
		if (ADBDObject* Owner = GetOwnerActorFromActorInfo())
		{
			// 수리 또는 상호작용이 완료되었을 경우 델리게이트
			Owner->GetInteractableComponent()->OnComplete.Broadcast();
			Owner->GetInteractableComponent()->OnCompleteSourceObject.Broadcast(Owner);
		}
	}
}

void UObjAbilitySystemComponent::DamageUpdated(const FOnAttributeChangeData& OnAttributeChangeData)
{
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;

	if (IsMaxAttribute(UObjAttributeSet::GetMaxDamageAttribute(), UObjAttributeSet::GetCurrentDamageAttribute()))
	{
		if (ADBDObject* Owner = GetOwnerActorFromActorInfo())
		{
			// 손상이 다 회복되었을 때
			//Owner->OnComplete.Broadcast();
			RemoveLooseGameplayTag(DBDGameplayTags::Object_Status_IsDestroy);
		}
	}
}

void UObjAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bCanDestroy)
	{
		// Current Damage 가 업데이트될때마다 델리게이트 연결
		GetGameplayAttributeValueChangeDelegate(UObjAttributeSet::GetCurrentDamageAttribute()).AddUObject(
			this, &ThisClass::DamageUpdated);
	}
	// Current Task 가 업데이트될때마다 델리게이트 연결
	GetGameplayAttributeValueChangeDelegate(UObjAttributeSet::GetCurrentTaskAttribute()).AddUObject(
		this, &ThisClass::TaskUpdated);
}


void UObjAbilitySystemComponent::AuthApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect, int32 Level)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(GameplayEffect, Level, MakeEffectContext());

		ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void UObjAbilitySystemComponent::ApplyInitializeEffects()
{
	if (!GetOwner() || !GetOwner()->HasAuthority())	return;

	if (!ObjDataAsset) return;
	
	for (const TSubclassOf<UGameplayEffect>& GE : ObjDataAsset->InitialEffects)
	{
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(GE, 1, MakeEffectContext());
		
		ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void UObjAbilitySystemComponent::OperatingInitializedAbilities()
{
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;

	if (!ObjDataAsset) return;
	
	for (const TSubclassOf<UGameplayAbility>& GA : ObjDataAsset->InitializedAbilities)
	{
		FGameplayAbilitySpec Spec = FGameplayAbilitySpec(GA, 1, -1, nullptr); 
		GiveAbilityAndActivateOnce(Spec);
	}

	if (ObjDataAsset->ActiveAbility)
	{
		FGameplayAbilitySpec Spec = FGameplayAbilitySpec(ObjDataAsset->ActiveAbility, 1, 1, nullptr);
		GiveAbility(Spec);
	}
}

void UObjAbilitySystemComponent::ServerSideInit()
{
	ApplyInitializeEffects();
	OperatingInitializedAbilities();
	InitializeAnimInstance();
}

void UObjAbilitySystemComponent::InitializeBaseAttributes()
{
}

void UObjAbilitySystemComponent::InitializeAnimInstance()
{
	if (AbilityActorInfo->GetAnimInstance())
	{
		if (UDBDObjectAnimInstance* AnimInstance = Cast<UDBDObjectAnimInstance>(AbilityActorInfo->GetAnimInstance()))
		{
			AnimInstance->InitializeWithAbilitySystem(this);
		}
	}
}

const UObjDataAsset* UObjAbilitySystemComponent::GetObjDataAsset() const
{
	if (ObjDataAsset)
	{
		return ObjDataAsset;
	}
	return nullptr;
}

bool UObjAbilitySystemComponent::IsMaxTask() const
{
	bool bFound = false;
	float CurrentTask = GetGameplayAttributeValue(UObjAttributeSet::GetCurrentTaskAttribute(), bFound);
	float MaxTask = GetGameplayAttributeValue(UObjAttributeSet::GetMaxTaskAttribute(), bFound);
	if (bFound && CurrentTask >= MaxTask)
	{
		return true;
	}
	return false;
}

bool UObjAbilitySystemComponent::IsMaxAttribute(const FGameplayAttribute& MaxAttribute,
	const FGameplayAttribute& CurrentAttribute)
{
	bool bFound = false;
	float CurrentValue = GetGameplayAttributeValue(CurrentAttribute, bFound);
	float MaxValue = GetGameplayAttributeValue(MaxAttribute, bFound);
	if (bFound && CurrentValue >= MaxValue)
	{
		return true;
	}
	return false;
}


