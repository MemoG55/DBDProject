// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GA/BaseAbility/GA_Survivor_Crouch.h"

#include "Shared/DBDGameplayTags.h"

UGA_Survivor_Crouch::UGA_Survivor_Crouch()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(DBDGameplayTags::Survivor_Ability_Passive_Crouch);
	ActivationOwnedTags.AddTag(DBDGameplayTags::Survivor_Status_Crouched);
	ActivationBlockedTags.AddTag(DBDGameplayTags::Survivor_Status_Dying);
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Survivor.Status.Captured")));
	ActivationBlockedTags.AddTag(DBDGameplayTags::Survivor_Status_MoveDisabled);
}

void UGA_Survivor_Crouch::InputReleased(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	if (IsActive())
	{
		K2_EndAbility();
	}
}

void UGA_Survivor_Crouch::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo,
                                          const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (K2_HasAuthority())
	{
		CrouchEffectHandle = BP_ApplyGameplayEffectToOwner(ChangeSpeedOnCrouchEffect);
	}
}

void UGA_Survivor_Crouch::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo,
                                     const FGameplayAbilityActivationInfo ActivationInfo,
                                     bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if (K2_HasAuthority() && CrouchEffectHandle.IsValid())
	{
		BP_RemoveGameplayEffectFromOwnerWithHandle(CrouchEffectHandle);
	}
}
