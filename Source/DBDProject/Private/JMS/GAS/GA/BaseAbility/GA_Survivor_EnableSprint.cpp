// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GA/BaseAbility/GA_Survivor_EnableSprint.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/GAS/SurvivorAbilitySystemComponent.h"
#include "JMS/GAS/SurvivorAttributeSet.h"
#include "JMS/GAS/GA/BaseAbility/GA_Survivor_Sprint.h"
#include "Shared/DBDGameplayTags.h"


UGA_Survivor_EnableSprint::UGA_Survivor_EnableSprint()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(DBDGameplayTags::Survivor_Ability_EnableSprint);
	ActivationBlockedTags.AddTag(DBDGameplayTags::Survivor_Status_Dying);
	ActivationOwnedTags.AddTag(DBDGameplayTags::Survivor_Status_SprintEnabled);
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
}

void UGA_Survivor_EnableSprint::InputPressed(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	if (!IsActive())
	{
		K2_ActivateAbility();
	}
}

void UGA_Survivor_EnableSprint::InputReleased(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo,
                                             const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	if (IsActive())
	{
		K2_EndAbility();
	}
}

void UGA_Survivor_EnableSprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
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
	GetSurvivorCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed =
		GetSurvivorAbilitySystemComponentFromActorInfo()->GetNumericAttribute(
			USurvivorAttributeSet::GetSprintSpeedAttribute());
}

void UGA_Survivor_EnableSprint::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo,
                                          const FGameplayAbilityActivationInfo ActivationInfo,
                                          bool bReplicateEndAbility,
                                          bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	GetSurvivorCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed =
		GetSurvivorAbilitySystemComponentFromActorInfo()->GetNumericAttribute(
			USurvivorAttributeSet::GetMovementSpeedAttribute());
	
	FGameplayTagContainer SprintAbilityTags;
	SprintAbilityTags.AddTag(DBDGameplayTags::Survivor_Ability_Passive_Sprint);
	GetSurvivorAbilitySystemComponentFromActorInfo()->CancelAbilities(&SprintAbilityTags);
}
