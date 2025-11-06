// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/GAS/GA_Kick_Generator_Killer.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "KMJ/Character/KillerCharacter.h"
#include "MMJ/Object/Interactable/Obj_Generator.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/Component/InteractableComponent.h"
#include "Shared/Component/InteractorComponent.h"


UGA_Kick_Generator_Killer::UGA_Kick_Generator_Killer()
{
}

void UGA_Kick_Generator_Killer::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                const FGameplayEventData* TriggerEventData)
{
	Killer = GetKillerCharacterFromActorInfo();
	
	if (!UDBDBlueprintFunctionLibrary::NativeActorHasTag(Killer->GetInteractorComponent()->GetCurrentInteractableActor(), DBDGameplayTags::Object_Status_IsActive)
		|| UDBDBlueprintFunctionLibrary::NativeActorHasTag(Killer->GetInteractorComponent()->GetCurrentInteractableActor(), DBDGameplayTags::Object_Status_IsInActive)
		|| UDBDBlueprintFunctionLibrary::NativeActorHasTag(Killer->GetInteractorComponent()->GetCurrentInteractableActor(), DBDGameplayTags::Object_Status_IsDestroy))
	{
		MontageStop();
		K2_CancelAbility();
	}
	/*if (UDBDBlueprintFunctionLibrary::NativeActorHasTag(Killer->GetInteractorComponent()->GetCurrentInteractableActor(), DBDGameplayTags::Object_Status_IsActive))*/
	else
	{
		MontageToPlay = IsLocallyControlled() ? KickMontageFPV : KickMontageTPV;

		UAbilityTask_PlayMontageAndWait* PlayLoopMontageTask =
			UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
				this, NAME_None, MontageToPlay, 1.f);
		PlayLoopMontageTask->OnCompleted.AddDynamic(this, &UGA_Kick_Generator_Killer::K2_EndAbility);
		PlayLoopMontageTask->OnBlendOut.AddDynamic(this, &UGA_Kick_Generator_Killer::K2_EndAbility);
		PlayLoopMontageTask->OnInterrupted.AddDynamic(this, &UGA_Kick_Generator_Killer::K2_CancelAbility);
		PlayLoopMontageTask->OnCancelled.AddDynamic(this, &UGA_Kick_Generator_Killer::K2_CancelAbility);
		PlayLoopMontageTask->ReadyForActivation();
	
		Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	}
}

void UGA_Kick_Generator_Killer::InputPressed(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	K2_ActivateAbility();
}

void UGA_Kick_Generator_Killer::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	MontageStop();
	K2_CancelAbility();
}

void UGA_Kick_Generator_Killer::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!bWasCancelled)
	{
		Killer->GetInteractorComponent()->InteractWithCurrentInteractable();
	}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	Killer->GetInteractorComponent()->EndInteraction();
}
