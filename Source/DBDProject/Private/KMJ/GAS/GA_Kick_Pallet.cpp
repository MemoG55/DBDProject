// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/GAS/GA_Kick_Pallet.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "KMJ/Character/KillerCharacter.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Component/InteractorComponent.h"


UGA_Kick_Pallet::UGA_Kick_Pallet()
{
}

void UGA_Kick_Pallet::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	Killer = GetKillerCharacterFromActorInfo();
	Killer->DisableInput(Cast<APlayerController>(Killer->GetController()));
	if (!UDBDBlueprintFunctionLibrary::NativeActorHasTag(Killer->GetInteractorComponent()->GetCurrentInteractableActor(), DBDGameplayTags::Object_Status_IsActive)
		|| UDBDBlueprintFunctionLibrary::NativeActorHasTag(Killer->GetInteractorComponent()->GetCurrentInteractableActor(), DBDGameplayTags::Object_Status_IsInActive)
		|| UDBDBlueprintFunctionLibrary::NativeActorHasTag(Killer->GetInteractorComponent()->GetCurrentInteractableActor(), DBDGameplayTags::Object_Status_IsDestroy))
	{
		MontageStop();
		K2_CancelAbility();
	}
	else
	{
		MontageToPlay = IsLocallyControlled() ? KickMontageFPV : KickMontageTPV;

		UAbilityTask_PlayMontageAndWait* PlayLoopMontageTask =
			UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
				this, NAME_None, MontageToPlay, 1.f);
		PlayLoopMontageTask->OnCompleted.AddDynamic(this, &UGA_Kick_Pallet::K2_EndAbility);
		PlayLoopMontageTask->OnBlendOut.AddDynamic(this, &UGA_Kick_Pallet::K2_EndAbility);
		PlayLoopMontageTask->OnInterrupted.AddDynamic(this, &UGA_Kick_Pallet::K2_CancelAbility);
		PlayLoopMontageTask->OnCancelled.AddDynamic(this, &UGA_Kick_Pallet::K2_CancelAbility);
		PlayLoopMontageTask->ReadyForActivation();
	
		Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	}
}

void UGA_Kick_Pallet::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	K2_ActivateAbility();
}

void UGA_Kick_Pallet::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if (!bWasCancelled)
	{
		Killer->GetInteractorComponent()->InteractWithCurrentInteractable();
	}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	Killer->GetInteractorComponent()->EndInteraction();
	Killer->EnableInput(Cast<APlayerController>(Killer->GetController()));
}
