// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/GAS/GA_Stun.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "KMJ/Character/KillerCharacter.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Component/InteractorComponent.h"


void UGA_Stun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                               const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	Killer = GetKillerCharacterFromActorInfo();
	Killer->DisableInput(Cast<APlayerController>(Killer->GetController()));

	if (Killer->IsCarriedSurvivorExist())
	{
		ASurvivorCharacter* CarriedSurvivor = Killer->GetCarriedSurvivorCharacter();
		CarriedSurvivor->SetSurvivorInjured();
		if (Killer->IsCarriedSurvivorExist())
		{
			Killer->ClearCarriedSurvivorCharacter();
			if (K2_HasAuthority())
			{
				UDBDBlueprintFunctionLibrary::RemoveTagFromActor(Killer, DBDGameplayTags::Killer_Common_Status_Carrying);
			}
			if (!K2_HasAuthority())
				Killer->Server_SetKiller_IsCarrying(Killer->IsCarriedSurvivorExist());
		}
	}

	MontageToPlay = IsLocallyControlled() ? StunMontageFPV : StunMontageTPV;

	UAbilityTask_PlayMontageAndWait* PlayLoopMontageTask =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this, NAME_None, MontageToPlay, 1.f);
	PlayLoopMontageTask->OnCompleted.AddDynamic(this, &UGA_Stun::K2_EndAbility);
	PlayLoopMontageTask->OnBlendOut.AddDynamic(this, &UGA_Stun::K2_EndAbility);
	PlayLoopMontageTask->OnInterrupted.AddDynamic(this, &UGA_Stun::K2_CancelAbility);
	PlayLoopMontageTask->OnCancelled.AddDynamic(this, &UGA_Stun::K2_CancelAbility);
	PlayLoopMontageTask->ReadyForActivation();
	
}

void UGA_Stun::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	Killer->EnableInput(Cast<APlayerController>(Killer->GetController()));
}
