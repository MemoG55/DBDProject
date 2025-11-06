// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Item/MedKit/GA/GA_MedKit_HealSelf.h"

#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/Component/SkillCheckComponent.h"
#include "JMS/DataAsset/DA_SurvivorMontage.h"
#include "JMS/GAS/ItemAbilitySystemComponent.h"
#include "JMS/GAS/SurvivorAbilitySystemComponent.h"
#include "JMS/GAS/SurvivorAttributeSet.h"
#include "JMS/GAS/GE/GE_HealSurvivorFromDying.h"
#include "JMS/GAS/GE/GE_HealSurvivor.h"
#include "JMS/GAS/GE/GE_HealSkillCheckBad.h"
#include "JMS/GAS/GE/GE_HealSkillCheckGreat.h"
#include "JMS/Item/MedKit/Item_MedKit.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/DBDDebugHelper.h"


UGA_MedKit_HealSelf::UGA_MedKit_HealSelf()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(DBDGameplayTags::Survivor_Ability_UseItem_MedKitHealSelf);
	ActivationRequiredTags.AddTag(DBDGameplayTags::Survivor_Status_Injured);
	ActivationBlockedTags.AddTag(DBDGameplayTags::Interactable_Character_Survivor);
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::OwnedTagPresent;
	TriggerData.TriggerTag = DBDGameplayTags::Item_Status_Using;
	AbilityTriggers.Add(TriggerData);
}


void UGA_MedKit_HealSelf::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo,
                                          const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	USurvivorAbilitySystemComponent* SurvivorASC = GetSurvivorAbilitySystemComponentFromActorInfo();
	if (!SurvivorASC)
	{
		return;
	}
	// Cost, Cooldown 등을 검사 + 점프 여부 검사
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	if (K2_HasAuthority())
	{
		FGameplayEffectContextHandle ContextHandle = SurvivorASC->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = SurvivorASC->MakeOutgoingSpec(
			NerfHealSpeedEffect, 0, ContextHandle);

		SpecHandle.Data->SetSetByCallerMagnitude(DBDGameplayTags::Survivor_SetbyCaller_Multiplier1,
		                                         Cast<AItem_MedKit>(GetEquippedItemFromActorInfo())->
		                                         GetNerfSelfHealSpeedMultiplier());
		NerfEffectHandle = SurvivorASC->BP_ApplyGameplayEffectSpecToSelf(SpecHandle);

		GetWorld()->GetTimerManager().SetTimer(HealTickTimerHandle, this, &UGA_MedKit_HealSelf::Heal, HealInterval,
		                                       true);
	}
	OnHealProgressChangedHandle = SurvivorASC->GetGameplayAttributeValueChangeDelegate(
		USurvivorAttributeSet::GetHealProgressAttribute()).AddUObject(
		this, &UGA_MedKit_HealSelf::OnHealProgressChanged);


	// PredictionKey는 클라이언트가 서버의 명령 없이 예측해서 실행할 때 사용 - 애니메이션 재생 등 중요한 로직이 아닐 경우
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		SurvivorASC->PlayMontage(this, ActivationInfo,
		                         GetSurvivorCharacterFromActorInfo()->SurvivorMontageData->HealSelf, 1.f);
		GetSurvivorCharacterFromActorInfo()->MoveEnabled(false);
	}
	if (IsLocallyControlled())
	{
		SetRandomSkillCheckEnabledOnClient();
	}
}

void UGA_MedKit_HealSelf::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo,
                                     const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                                     bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if (GetAnimInstance())
	{
		GetAnimInstance()->StopAllMontages(0.1f);
	}

	if (K2_HasAuthority())
	{
		GetAbilitySystemComponentFromActorInfo()->RemoveActiveGameplayEffect(NerfEffectHandle);
	}
	GetAbilitySystemComponentFromActorInfo()->GetGameplayAttributeValueChangeDelegate(
		USurvivorAttributeSet::GetHealProgressAttribute()).Remove(OnHealProgressChangedHandle);
	GetWorld()->GetTimerManager().ClearTimer(HealTickTimerHandle);
	GetSurvivorCharacterFromActorInfo()->MoveEnabled(true);
}

void UGA_MedKit_HealSelf::Heal()
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

void UGA_MedKit_HealSelf::OnHealProgressChanged(const FOnAttributeChangeData& Data)
{
	float NewValue = Data.NewValue;
	float MaxValue = GetSurvivorAbilitySystemComponentFromActorInfo()->GetNumericAttribute(
		USurvivorAttributeSet::GetMaxHealProgressAttribute());
	Debug::Print(1111, TEXT("JMS1111: OnHealProgressChanged NewValue: %f, MaxValue: %f"), NewValue, MaxValue);
	if (NewValue >= MaxValue)
	{
		K2_EndAbility();
	}
	ProgressPercentage = NewValue / MaxValue;
}

void UGA_MedKit_HealSelf::Server_SendSkillCheckResult_Implementation(ESkillCheckResult Result)
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
}
