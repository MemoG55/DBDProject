// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/GAS/GA_Hook_Killer.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Components/CapsuleComponent.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/DataAsset/DA_SurvivorMontage.h"
#include "KMJ/Character/KillerCharacter.h"
#include "MMJ/Object/Interactable/Obj_Hook.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Component/InteractorComponent.h"


void UGA_Hook_Killer::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo,
                                      const FGameplayAbilityActivationInfo ActivationInfo,
                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	Killer = GetKillerCharacterFromActorInfo();

	AObj_Hook* Hook = Cast<AObj_Hook>(Killer->GetInteractorComponent()->GetCurrentInteractableActor());
	if (Hook)
	{
		FName SocketName = FName(TEXT("socket_KillerAttach"));

		// 소켓 위치 가져오기
		FRotator SocketRotation = Hook->GetSkeletalMeshComponent()->GetSocketRotation(SocketName);
		UDBDBlueprintFunctionLibrary::MoveCharacterWithRotationAdjust(Hook->GetSkeletalMeshComponent(), FName(TEXT("AttachKillerSocket")),Killer,Killer->GetActorRotation(),FName("joint_Char"));
		AController* Controller = Killer->GetController();
		if (Controller)
		{
			Controller->SetControlRotation(SocketRotation);
		}
	}
	
	Killer->DisableInput(Cast<APlayerController>(Killer->GetController()));
	if (Killer->IsCarriedSurvivorExist())
	{
		Killer->GetInteractorComponent()->InteractWithCurrentInteractable();
		if (IsLocallyControlled())
		{
			UAbilityTask_PlayMontageAndWait* PlayLoopMontageTask =
				UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
					this, NAME_None, FPVHookMontage, 1.f);
			PlayLoopMontageTask->OnCompleted.AddDynamic(this, &UGA_Hook_Killer::K2_EndAbility);
			PlayLoopMontageTask->OnBlendOut.AddDynamic(this, &UGA_Hook_Killer::K2_EndAbility);
			PlayLoopMontageTask->OnInterrupted.AddDynamic(this, &UGA_Hook_Killer::K2_CancelAbility);
			PlayLoopMontageTask->OnCancelled.AddDynamic(this, &UGA_Hook_Killer::K2_CancelAbility);
			PlayLoopMontageTask->ReadyForActivation();
		}
		else
		{
			UAbilityTask_PlayMontageAndWait* PlayLoopMontageTask =
				UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
					this, NAME_None, TPVHookMontage, 1.f);
			PlayLoopMontageTask->OnCompleted.AddDynamic(this, &UGA_Hook_Killer::K2_EndAbility);
			PlayLoopMontageTask->OnBlendOut.AddDynamic(this, &UGA_Hook_Killer::K2_EndAbility);
			PlayLoopMontageTask->OnInterrupted.AddDynamic(this, &UGA_Hook_Killer::K2_CancelAbility);
			PlayLoopMontageTask->OnCancelled.AddDynamic(this, &UGA_Hook_Killer::K2_CancelAbility);
			PlayLoopMontageTask->ReadyForActivation();
		}
		
	}
	else K2_CancelAbility();
}

void UGA_Hook_Killer::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                                 bool bWasCancelled)
{
	if (!bWasCancelled)
	{
		Killer->GetCapsuleComponent()->ClearMoveIgnoreActors();
		if (K2_HasAuthority())
		{
			UDBDBlueprintFunctionLibrary::RemoveTagFromActor(Killer, DBDGameplayTags::Killer_Common_Status_Carrying);
			UDBDBlueprintFunctionLibrary::RemoveTagFromActor(Killer, DBDGameplayTags::Killer_Common_Status_Hooking);
			Killer->GetInteractorComponent()->EndInteraction();
		}
		Killer->ClearCarriedSurvivorCharacter();
		if (!K2_HasAuthority())
			Killer->Server_SetKiller_IsCarrying(Killer->IsCarriedSurvivorExist());
	}
	Killer->EnableInput(Cast<APlayerController>(Killer->GetController()));
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
