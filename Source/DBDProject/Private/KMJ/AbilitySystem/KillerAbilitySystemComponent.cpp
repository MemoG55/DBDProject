// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/AbilitySystem/KillerAbilitySystemComponent.h"

#include "KMJ/Character/KillerHuntress.h"
#include "KMJ/DataAsset/DA_KillerGameplayAbilities.h"


UKillerAbilitySystemComponent::UKillerAbilitySystemComponent()
{
	//Delegate 나중에 연결할 거 있으면 연결
}

void UKillerAbilitySystemComponent::ApplyInitializeEffects()
{
	//서버에서만 수행
	if (!GetOwner() || !GetOwner()->HasAuthority())
		return;
	
	for (const TSubclassOf<UGameplayEffect>& GEClass : GAData->InitialEffects)
	{
		//GE스펙핸들 생성
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(GEClass, 1, MakeEffectContext());
		//자기 자신에게 GE 적용
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}

void UKillerAbilitySystemComponent::OperatingInitializedAbilities()
{
	//서버에서만 수행
	if (!GetOwner() || !GetOwner()->HasAuthority())
		return;

	//초기세팅 어빌리티 부여
	for (const TSubclassOf<UGameplayAbility>& GAClass : GAData->InitializedAbilities)
	{
		FGameplayAbilitySpec Spec = FGameplayAbilitySpec(GAClass, 1, -1, nullptr);
		//어빌리티 부여 및 한번만 실행
		GiveAbilityAndActivateOnce(Spec, nullptr);
	}

	//기본 능력 어빌리티 부여
	for (const TPair<EKillerAbilityInputID, TSubclassOf<UGameplayAbility>>& GAClassPair : GAData->BaseAbilities)
	{
		GiveAbility(FGameplayAbilitySpec(GAClassPair.Value, 0, (int32)GAClassPair.Key, nullptr));
	}

	//특수 능력 어빌리티 부여
	for (const TPair<EKillerAbilityInputID, TSubclassOf<UGameplayAbility>>& GAClassPair : GAData->SkillAbilities)
	{
		//InLevel이 0인 이유: 초기상태이므로 스킬 해금이 되지 않음을 판단하는 수단으로 사용가능
		GiveAbility(FGameplayAbilitySpec(GAClassPair.Value, 0, (int32)GAClassPair.Key, nullptr));
	}

	// 델리게이트 연결
	if (AKillerHuntress* KillerHuntress = Cast<AKillerHuntress>(GetOwner()))
	{
		// 어빌리티 부여 후 캐릭터의 OnAbilityGranted 델리게이트를 연결
		KillerHuntress->OnAbilityGrantedDelegate.Broadcast();
	}
}

void UKillerAbilitySystemComponent::ApplyFullStatEffect()
{
	//이게 무슨 역할이더라
	//FullStat GE는 2번
	AuthApplyGameplayEffect(GAData->InitialEffects[1], 1);
}

void UKillerAbilitySystemComponent::AuthApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect, int Level)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(GameplayEffect, Level, MakeEffectContext());
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}
