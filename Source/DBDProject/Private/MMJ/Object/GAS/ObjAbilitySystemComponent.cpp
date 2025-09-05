// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/ObjAbilitySystemComponent.h"

#include "MMJ/Object/DBDObject.h"
#include "MMJ/Object/DataAsset/ObjDataAsset.h"
#include "MMJ/Object/GAS/ObjAttributeSet.h"
#include "Shared/DBDGameplayTags.h"

UObjAbilitySystemComponent::UObjAbilitySystemComponent()
{
	// Current Task 가 업데이트될때마다 델리게이트 연결
	GetGameplayAttributeValueChangeDelegate(UObjAttributeSet::GetCurrentTaskAttribute()).AddUObject(
		this, &ThisClass::TaskUpdated);
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
			Owner->OnComplete.Broadcast();
			AddLooseGameplayTag(DBDGameplayTags::Object_Status_IsComplete);
			RemoveLooseGameplayTag(DBDGameplayTags::Object_Status_IsActive);
		}
	}
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

	for (const TSubclassOf<UGameplayEffect>& GE : ObjDataAsset->InitialEffects)
	{
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(GE, 1, MakeEffectContext());
		
		ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void UObjAbilitySystemComponent::OperatingInitializedAbilities()
{
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;
	
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
}

void UObjAbilitySystemComponent::InitializeBaseAttributes()
{
}

const UObjDataAsset* UObjAbilitySystemComponent::GetObjDataAsset() const
{
	return ObjDataAsset;
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


