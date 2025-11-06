// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Item/ItemGameplayAbility_Charge.h"

#include "AbilitySystemComponent.h"
#include "JMS/GAS/ItemAbilitySystemComponent.h"
#include "JMS/GAS/ItemAttributeSet.h"
#include "JMS/GAS/SurvivorAbilitySystemComponent.h"
#include "JMS/GAS/SurvivorAttributeSet.h"


bool UItemGameplayAbility_Charge::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                     const FGameplayAbilityActorInfo* ActorInfo,
                                                     const FGameplayTagContainer* SourceTags,
                                                     const FGameplayTagContainer* TargetTags,
                                                     FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	UAbilitySystemComponent* ASC = GetSurvivorAbilitySystemComponentFromActorInfo();
	const USurvivorAttributeSet* Attr = ASC->GetSet<USurvivorAttributeSet>();

	float CurrentCharge = Attr->GetCurrentItemCharge();
	if (CurrentCharge <= 0.0f)
	{
		return false;
	}
	return true;
}

void UItemGameplayAbility_Charge::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                  const FGameplayAbilityActorInfo* ActorInfo,
                                                  const FGameplayAbilityActivationInfo ActivationInfo,
                                                  const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (K2_HasAuthority())
	{
		// FTimerHandle TickHandle;
		// GetWorld()->GetTimerManager().SetTimer(TickHandle, this, &UItemGameplayAbility_Charge::OnTimerTick, 0.1f, true);

		if (ChargeConsumptionEffect)
		{
			ChargeConsumptionEffectHandle = GetSurvivorAbilitySystemComponentFromActorInfo()->
				BP_ApplyGameplayEffectToSelf(
					ChargeConsumptionEffect, 0, GetSurvivorAbilitySystemComponentFromActorInfo()->MakeEffectContext());
		}
		ChargeChangedDelegateHandle = GetSurvivorAbilitySystemComponentFromActorInfo()->
		                              GetGameplayAttributeValueChangeDelegate(
			                              USurvivorAttributeSet::GetCurrentItemChargeAttribute()).AddUObject(
			                              this, &UItemGameplayAbility_Charge::OnCurrentItemChargeChanged);
	}
}

void UItemGameplayAbility_Charge::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo,
                                             const FGameplayAbilityActivationInfo ActivationInfo,
                                             bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if (ChargeConsumptionEffectHandle.IsValid())
	{
		GetSurvivorAbilitySystemComponentFromActorInfo()->RemoveActiveGameplayEffect(ChargeConsumptionEffectHandle);
	}
	GetSurvivorAbilitySystemComponentFromActorInfo()->
		GetGameplayAttributeValueChangeDelegate(USurvivorAttributeSet::GetCurrentItemChargeAttribute()).Remove(
			ChargeChangedDelegateHandle);
}

void UItemGameplayAbility_Charge::OnCurrentItemChargeChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
	if (OnAttributeChangeData.NewValue <= 0)
	{
		K2_EndAbility();
	}
}
