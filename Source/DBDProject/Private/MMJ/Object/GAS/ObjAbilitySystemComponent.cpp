// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/ObjAbilitySystemComponent.h"

#include "MMJ/Object/DBDObject.h"
#include "MMJ/Object/DataAsset/ObjDataAsset.h"
#include "MMJ/Object/GAS/ObjAttributeSet.h"

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

	if (IsMaxTask()) return;

	bool bFound = false;
	float MaxTask = GetGameplayAttributeValue(UObjAttributeSet::GetMaxTaskAttribute(), bFound);
	
	if (bFound && OnAttributeChangeData.NewValue >= MaxTask)
	{
		if (ADBDObject* Owner = GetOwnerActorFromActorInfo())
		{
			// 수리 또는 상호작용이 완료되었을 경우 델리게이트
			Owner->OnComplete.Execute();
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
		UE_LOG(LogTemp, Warning, TEXT("ActiveAbility Set in %s -> %s"), *GetOwner()->GetName(), *ObjDataAsset->ActiveAbility->GetName() );
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

bool UObjAbilitySystemComponent::IsMaxTask() const
{
	return false;
}


