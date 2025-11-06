// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/GAS/GA_Drop.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/DataAsset/DA_SurvivorMontage.h"
#include "JMS/GAS/GA/Passive/GA_Survivor_CapturedByKiller.h"
#include "KMJ/Character/KillerCharacter.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Component/InteractorComponent.h"

void UGA_Drop::SetSurvivorGAClearAndDetach()
{
    Killer = GetKillerCharacterFromActorInfo();
    if (Killer)
    {
        if (CarriedSurvivor)
        {
            UAbilitySystemComponent* ASC = CarriedSurvivor->GetAbilitySystemComponent();

            if (ASC)
            {
                const FGameplayAbilitySpec* MatchingSpec = nullptr;

                // ASC에 등록된 모든 AbilitySpec을 순회
                for (FGameplayAbilitySpec& Spec : ASC->GetActivatableAbilities())
                {
                    if (Spec.Ability && Spec.Ability->IsA(UGA_Survivor_CapturedByKiller::StaticClass()))
                    {
                        if (Spec.IsActive())
                        {
                            ASC->CancelAbility(Spec.Ability);
                            break; // 하나만 종료하고 끝내려면 break
                        }
                    }
                }
            }
        }
    }
    else return;
}

void UGA_Drop::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    Killer = GetKillerCharacterFromActorInfo();
    Killer->DisableInput(Cast<APlayerController>(Killer->GetController()));
    CarriedSurvivor = Killer->GetCarriedSurvivorCharacter();
    if (K2_HasAuthority())
    {
        CarriedSurvivor->PlaySyncMontageFromServer(CarriedSurvivor->SurvivorMontageData->DroppedFromKiller);
    }
    MontageToPlay = IsLocallyControlled() ? FPVDropMontage : TPVDropMontage;
    if (Killer->IsCarriedSurvivorExist())
    {
        UAbilityTask_PlayMontageAndWait* PlayLoopMontageTask =
            UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
                this, NAME_None, MontageToPlay, 1.f);
        PlayLoopMontageTask->OnCompleted.AddDynamic(this, &UGA_Drop::K2_EndAbility);
        PlayLoopMontageTask->OnBlendOut.AddDynamic(this, &UGA_Drop::K2_EndAbility);
        PlayLoopMontageTask->OnInterrupted.AddDynamic(this, &UGA_Drop::K2_EndAbility);
        PlayLoopMontageTask->OnCancelled.AddDynamic(this, &UGA_Drop::K2_EndAbility);
        PlayLoopMontageTask->ReadyForActivation();
    }
}

void UGA_Drop::OnDrop()
{
    //Killer->GetCarriedSurvivorCharacter()->SetActorLocation(FVector(Killer->GetCarriedSurvivorCharacter()->GetActorLocation().X, Killer->GetCarriedSurvivorCharacter()->GetActorLocation().Y, Killer->GetActorLocation().Z));
    K2_EndAbility();
}

void UGA_Drop::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                          const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Killer->GetInteractorComponent()->EndInteraction();
    if (CarriedSurvivor)
    {
        // SurvivorCharacter 내려놓는 위치 조정
        CarriedSurvivor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        CarriedSurvivor->SetSurvivorDying();
        // UDBDBlueprintFunctionLibrary::MoveCharacterWithRotationAdjust(Killer->GetMesh(), FName(TEXT("SurvivorSocket")),CarriedSurvivor,FRotator(0.f,90.f,0.f),FName("joint_Char"));
        CarriedSurvivor->SetCollisionAndGravityEnabled(true);
        // JMS: 튕겨나가는 이유가 MOVE_Falling처리 되어서 낙하 동작을 하기 때문
        CarriedSurvivor->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
        Killer->ClearCarriedSurvivorCharacter();
    }
    
    if (K2_HasAuthority())
    {
        UDBDBlueprintFunctionLibrary::RemoveTagFromActor(Killer, DBDGameplayTags::Killer_Common_Status_Carrying);
        UDBDBlueprintFunctionLibrary::RemoveTagFromActor(Killer, DBDGameplayTags::Killer_Common_Status_Hooking);
    }
    if (!K2_HasAuthority())
        Killer->Server_SetKiller_IsCarrying(Killer->IsCarriedSurvivorExist());
    Killer->GetCapsuleComponent()->ClearMoveIgnoreActors();
    Killer->EnableInput(Cast<APlayerController>(Killer->GetController()));
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}



