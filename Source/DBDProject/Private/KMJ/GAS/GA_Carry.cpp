// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/GAS/GA_Carry.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "KMJ/AbilitySystem/KillerAttributeSet.h"
#include "KMJ/Character/KillerCharacter.h"
#include "MMJ/Object/Interactable/Obj_Hook.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Component/InteractableComponent.h"
#include "Shared/Component/InteractorComponent.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/Subsystem/DBDObjectObserver.h"


UGA_Carry::UGA_Carry()
{
}

void UGA_Carry::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//UE_LOG(LogTemp, Warning, TEXT("UGA_Carry::ActivateAbility"));

	//Killer 존재�는지 �인
	Killer = GetKillerCharacterFromActorInfo();
	if (Killer == nullptr)
	{
		//UE_LOG(LogTemp,Error, TEXT("KillerActor: Nullptr"));
		K2_CancelAbility();
		return;
	}
	//UE_LOG(LogTemp,Warning, TEXT("KillerActor: %s"), *Killer->GetName());
	//KillerInteractWithCurrentInteractable �행
	Killer->GetInteractorComponent()->InteractWithCurrentInteractable();
	if (Killer->IsCarriedSurvivorExist())
	{
		K2_CancelAbility();
		return;
	}
	//Interact 가�한 Survivor �는지 �인
	InteractableSurvivorCharacter = GetInteractableSurvivorCharacter();
	if (InteractableSurvivorCharacter == nullptr)
	{
		//UE_LOG(LogTemp,Error, TEXT("InteractableSurvivorCharacter: Nullptr"));	
		K2_CancelAbility();
		return;
	}
	Killer->SetCarriedSurvivorCharacter(InteractableSurvivorCharacter);
	Killer->DisableInput(Cast<APlayerController>(Killer->GetController()));
	Killer->GetCapsuleComponent()->IgnoreActorWhenMoving(InteractableSurvivorCharacter, true);

	if (IsLocallyControlled())
	{
		UAbilityTask_PlayMontageAndWait* PlayLoopMontageTask =
	UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, NAME_None, FPVStartMontage, Killer->KillerAttributeSet->PickUpSpeedRate.GetCurrentValue());
		PlayLoopMontageTask->OnCompleted.AddDynamic(this, &UGA_Carry::K2_EndAbility);
		PlayLoopMontageTask->OnBlendOut.AddDynamic(this, &UGA_Carry::K2_EndAbility);
		PlayLoopMontageTask->OnInterrupted.AddDynamic(this, &UGA_Carry::K2_CancelAbility);
		PlayLoopMontageTask->OnCancelled.AddDynamic(this, &UGA_Carry::K2_CancelAbility);
		PlayLoopMontageTask->ReadyForActivation();
	}
	else
	{
		UAbilityTask_PlayMontageAndWait* PlayLoopMontageTask =
	UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, NAME_None, TPVStartMontage, Killer->KillerAttributeSet->PickUpSpeedRate.GetCurrentValue());
		PlayLoopMontageTask->OnCompleted.AddDynamic(this, &UGA_Carry::K2_EndAbility);
		PlayLoopMontageTask->OnBlendOut.AddDynamic(this, &UGA_Carry::K2_EndAbility);
		PlayLoopMontageTask->OnInterrupted.AddDynamic(this, &UGA_Carry::K2_CancelAbility);
		PlayLoopMontageTask->OnCancelled.AddDynamic(this, &UGA_Carry::K2_CancelAbility);
		PlayLoopMontageTask->ReadyForActivation();
	}
	UDBDBlueprintFunctionLibrary::AddUniqueTagToActor(Killer, DBDGameplayTags::Killer_Common_Status_Carrying);
	if (!K2_HasAuthority())
		Killer->Server_SetKiller_IsCarrying(UDBDBlueprintFunctionLibrary::NativeActorHasTag(Killer, DBDGameplayTags::Killer_Common_Status_Carrying));
}

void UGA_Carry::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!bWasCancelled)
	{
		Killer->SetCarriedSurvivorCharacter(InteractableSurvivorCharacter);
	}
	Killer->GetInteractorComponent()->EndInteraction();
	Killer->EnableInput(Cast<APlayerController>(Killer->GetController()));
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
