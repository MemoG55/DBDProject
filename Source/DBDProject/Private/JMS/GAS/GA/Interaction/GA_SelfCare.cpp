// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GA/Interaction/GA_SelfCare.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/Component/SkillCheckComponent.h"
#include "JMS/DataAsset/DA_SurvivorMontage.h"
#include "JMS/GAS/SurvivorAttributeSet.h"
#include "JMS/GAS/GE/GE_HealSurvivorFromDying.h"
#include "JMS/GAS/GE/GE_HealSurvivor.h"
#include "JMS/GAS/GE/GE_HealSkillCheckBad.h"
#include "JMS/GAS/GE/GE_HealSkillCheckGreat.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/Component/InteractableComponent.h"
#include "Shared/Component/InteractorComponent.h"


UGA_SelfCare::UGA_SelfCare()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(DBDGameplayTags::Survivor_Ability_Perk_HealSelf);
	ActivationRequiredTags.AddTag(DBDGameplayTags::Survivor_Status_Injured);
	ActivationOwnedTags.AddTag(DBDGameplayTags::Survivor_Status_MoveDisabled);
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Interactable")));
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
}

void UGA_SelfCare::InputPressed(const FGameplayAbilitySpecHandle Handle,
                                const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	if (!IsActive())
	{
		K2_ActivateAbility();
	}
}

void UGA_SelfCare::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                   const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo,
                                   const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	if (K2_HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimer(HealTickTimerHandle, this, &UGA_SelfCare::Heal, HealInterval, true);
	}
	OnHealProgressChangedHandle = GetAbilitySystemComponentFromActorInfo()->GetGameplayAttributeValueChangeDelegate(
		USurvivorAttributeSet::GetHealProgressAttribute()).AddUObject(this, &UGA_SelfCare::OnHealProgressChanged);
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		GetAbilitySystemComponentFromActorInfo()->PlayMontage(this, ActivationInfo,
		                                                      GetSurvivorCharacterFromActorInfo()->SurvivorMontageData->
		                                                      HealSelf, 1.f);
		GetSurvivorCharacterFromActorInfo()->MoveEnabled(false);
	}
	if (IsLocallyControlled())
	{
		SetRandomSkillCheckEnabledOnClient();
	}
}

void UGA_SelfCare::InputReleased(const FGameplayAbilitySpecHandle Handle,
                                 const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	if (IsActive())
	{
		K2_EndAbility();
	}
}

void UGA_SelfCare::EndAbility(const FGameplayAbilitySpecHandle Handle,
                              const FGameplayAbilityActorInfo* ActorInfo,
                              const FGameplayAbilityActivationInfo ActivationInfo,
                              bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if (GetAnimInstance())
	{
		GetAnimInstance()->StopAllMontages(0.1f);
	}


	GetAbilitySystemComponentFromActorInfo()->GetGameplayAttributeValueChangeDelegate(
		USurvivorAttributeSet::GetHealProgressAttribute()).Remove(OnHealProgressChangedHandle);
	GetWorld()->GetTimerManager().ClearTimer(HealTickTimerHandle);
	GetSurvivorCharacterFromActorInfo()->MoveEnabled(true);
}

void UGA_SelfCare::Server_SendSkillCheckResult_Implementation(ESkillCheckResult Result)
{
	FGameplayEffectSpecHandle ResultEffectSpecHandle;
	switch (Result)
	{
	case ESkillCheckResult::Bad:
		ResultEffectSpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
			UGE_HealSkillCheckBad::StaticClass(), 0, GetAbilitySystemComponentFromActorInfo()->MakeEffectContext());
		GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToSelf(*ResultEffectSpecHandle.Data.Get());
		break;

	case ESkillCheckResult::Great:
		ResultEffectSpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
			UGE_HealSkillCheckGreat::StaticClass(), 0,
			GetAbilitySystemComponentFromActorInfo()->MakeEffectContext());
		GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToSelf(*ResultEffectSpecHandle.Data.Get());
		break;
	default:
		break;
	}
	// if (!CheckAuthority()) return;
	//
	// if (Data.EventTag.IsValid() && Data.EventTag == DBDGameplayTags::Object_Event_Check)
	// {
	// 	// 스킬체크 대성공 보너스
	// 	if (Data.InstigatorTags.HasTag(DBDGameplayTags::Object_Event_Result_Success)
	// 		&& !OwningObjectASC->GetObjDataAsset()->SkillCheckSuccessEffects.IsEmpty())
	// 	{
	// 		for (const FObjGEStruct GE : OwningObjectASC->GetObjDataAsset()->SkillCheckSuccessEffects)
	// 		{
	// 			FGameplayEffectSpecHandle SpecHandle = OwningObjectASC->MakeOutgoingSpec(
	// 				GE.GameplayEffect, 1, OwningObjectASC->MakeEffectContext());
	// 			OwningObjectASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	// 		}
	// 	}
	// 	// 스킬체크 실패 페널티 (진행도 감소 + 알림 + 상호작용 불가)
	// 	if (Data.InstigatorTags.HasTag(DBDGameplayTags::Object_Event_Result_Failure)
	// 		&& !OwningObjectASC->GetObjDataAsset()->SkillCheckSuccessEffects.IsEmpty())
	// 	{
	// 		for (const FObjGEStruct GE : OwningObjectASC->GetObjDataAsset()->SkillCheckFailureEffects)
	// 		{
	// 			FGameplayEffectSpecHandle SpecHandle = OwningObjectASC->MakeOutgoingSpec(
	// 				GE.GameplayEffect, 1, OwningObjectASC->MakeEffectContext());
	// 			OwningObjectASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	// 		}
	// 	}
	// }
}

void UGA_SelfCare::Heal()
{
	float HealSpeed = GetAbilitySystemComponentFromActorInfo()->GetNumericAttribute(
		USurvivorAttributeSet::GetHealSpeedAttribute());
	// 일반적인 치료의 35%의 속도로 치료
	HealSpeed *= 0.35f;

	FGameplayEffectContextHandle SpecContext = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	SpecContext.AddSourceObject(GetAvatarActorFromActorInfo());
	SpecContext.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		UGE_HealSurvivor::StaticClass(), 1, SpecContext);
	SpecHandle.Data->SetSetByCallerMagnitude(DBDGameplayTags::Survivor_SetbyCaller_HealAmount,
	                                         HealSpeed / (1.f / HealInterval));
	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void UGA_SelfCare::OnHealProgressChanged(const FOnAttributeChangeData& Data)
{
	float NewValue = Data.NewValue;
	float MaxValue = GetAbilitySystemComponentFromActorInfo()->GetNumericAttribute(
		USurvivorAttributeSet::GetMaxHealProgressAttribute());
	if (NewValue >= MaxValue)
	{
		K2_EndAbility();
	}
	ProgressPercentage = NewValue / MaxValue;
}
