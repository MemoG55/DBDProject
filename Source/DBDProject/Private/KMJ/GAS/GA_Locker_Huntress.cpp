// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/GAS/GA_Locker_Huntress.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "KMJ/AbilitySystem/HuntressAttributeSet.h"
#include "KMJ/Character/KillerCharacter.h"
#include "KMJ/Character/KillerHuntress.h"
#include "MMJ/Object/Interactable/Obj_Cabinet.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Component/InteractorComponent.h"


void UGA_Locker_Huntress::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Killer = GetKillerCharacterFromActorInfo();
	Huntress = Cast<AKillerHuntress>(Killer);
	Killer->DisableInput(Cast<APlayerController>(Killer->GetController()));

	Killer->GetInteractorComponent()->InteractWithCurrentInteractable();

	AObj_Cabinet* Cabinet = Cast<AObj_Cabinet>(Huntress->GetInteractorComponent()->GetCurrentInteractableActor());
	if (Cabinet)
	{
		FName SocketName = FName(TEXT("AttachKillerSocket"));

		// 소켓 위치 가져오기
		FRotator SocketRotation = Cabinet->GetSkeletalMeshComponent()->GetSocketRotation(SocketName);
		UDBDBlueprintFunctionLibrary::MoveCharacterWithRotationAdjust(Cabinet->GetSkeletalMeshComponent(), FName(TEXT("AttachKillerSocket")),Huntress,Huntress->GetActorRotation(),FName("joint_Char"));
		AController* Controller = Killer->GetController();
		if (Controller)
		{
			Controller->SetControlRotation(SocketRotation);
		}
	}

	MontageToPlay = IsLocallyControlled() ? FPVSearchMontage : TPVSearchMontage;
	//PlayMontage(MontageToPlay);
	UAbilityTask_PlayMontageAndWait* PlayLoopMontageTask =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this, NAME_None, MontageToPlay, 1.f);
	PlayLoopMontageTask->OnInterrupted.AddDynamic(this, &UGA_Locker_Huntress::K2_CancelAbility);
	PlayLoopMontageTask->OnCancelled.AddDynamic(this, &UGA_Locker_Huntress::K2_CancelAbility);
	PlayLoopMontageTask->ReadyForActivation();

	//생존자 잡는 조건 추가:R2 
	//if ()
	//R3. RefillAxe
	if (!UDBDBlueprintFunctionLibrary::NativeActorHasTag(Huntress, DBDGameplayTags::Killer_Huntress_Status_AxeFull))
	{
		//Huntress->Multicast_SetLeftAxeVisibility(true);
		MontageToPlay = IsLocallyControlled() ? FPVRefillMontage : TPVRefillMontage;
		PlayMontage(MontageToPlay);
		Huntress->HuntressAttributeSet->SetCurrentAxeNum(Huntress->HuntressAttributeSet->AxeNumber.GetBaseValue());
		UDBDBlueprintFunctionLibrary::AddUniqueTagToActor(Huntress, DBDGameplayTags::Killer_Huntress_Status_AxeFull);
	}
	//R1. Nothing
	else
	{
		MontageToPlay = IsLocallyControlled() ? FPVNoneMontage : TPVNoneMontage;
		PlayMontage(MontageToPlay);
	}
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGA_Locker_Huntress::InputPressed(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	K2_ActivateAbility();
}

void UGA_Locker_Huntress::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                     bool bReplicateEndAbility, bool bWasCancelled)
{
	Killer->GetInteractorComponent()->EndInteraction();
	//Huntress->Multicast_SetLeftAxeVisibility(false);
	Killer->EnableInput(Cast<APlayerController>(Killer->GetController()));
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_Locker_Huntress::PlayMontage(UAnimMontage* Montage)
{
	UAbilityTask_PlayMontageAndWait* PlayLoopMontageTask =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this, NAME_None, Montage, 1.f);
	PlayLoopMontageTask->OnCompleted.AddDynamic(this, &UGA_Locker_Huntress::K2_EndAbility);
	PlayLoopMontageTask->OnBlendOut.AddDynamic(this, &UGA_Locker_Huntress::K2_EndAbility);
	PlayLoopMontageTask->OnInterrupted.AddDynamic(this, &UGA_Locker_Huntress::K2_CancelAbility);
	PlayLoopMontageTask->OnCancelled.AddDynamic(this, &UGA_Locker_Huntress::K2_CancelAbility);
	PlayLoopMontageTask->ReadyForActivation();
}