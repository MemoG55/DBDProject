// Fill out your copyright notice in the Description page of Project Settings.
// 생존자가 갈고리에 걸릴 때 애니메이션을 재생하고 근처의 갈고리에 붙습니다.
// TODO: 갈고리를 검색하지 않는 방법을 고려

#include "JMS/GAS/GA/Passive/GA_SurvivorHookedIn.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MMJ/Object/Interactable/Obj_Hook.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDGameplayTags.h"


UGA_SurvivorHookedIn::UGA_SurvivorHookedIn()
{
	AbilityTags.AddTag(DBDGameplayTags::Survivor_Ability_Passive_HookedIn);
	ActivationOwnedTags.AddTag(DBDGameplayTags::Survivor_Status_MoveDisabled);
	BlockAbilitiesWithTag.AddTag(DBDGameplayTags::Survivor_Ability_Passive_Hooked);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::OwnedTagAdded;
	TriggerData.TriggerTag = DBDGameplayTags::Survivor_Status_Hooked;
	AbilityTriggers.Add(TriggerData);
}

void UGA_SurvivorHookedIn::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!ASC)
	{
		return;
	}
	if (K2_HasAuthority())
	{
		// TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		// ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
		// TArray<AActor*> ActorsToIgnore;
		// ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
		// TArray<AActor*> OutActors;
		// UKismetSystemLibrary::SphereOverlapActors(GetAvatarActorFromActorInfo(),
		//                                           GetAvatarActorFromActorInfo()->GetActorLocation(), 500.f, ObjectTypes,
		//                                           AObj_Hook::StaticClass(), ActorsToIgnore, OutActors);
		// DrawDebugSphere(GetWorld(), GetAvatarActorFromActorInfo()->GetActorLocation(), 500.f, 10, FColor::Red, true);
		// if (OutActors.IsEmpty())
		// {
		// 	Debug::Print(TEXT("JMS11: UGA_SurvivorHooked : No HookClass Nearby"), 11);
		// 	K2_EndAbility();
		// 	return;
		// }
		//
		// CachedHook = Cast<AObj_Hook>(OutActors.Top());
		// if (!CachedHook)
		// {
		// 	Debug::Print(TEXT("JMS12: UGA_SurvivorHooked : No HookInstance Nearby"), 12);
		// 	K2_EndAbility();
		// 	return;
		// }
		AObj_Hook* CurrentHook = GetSurvivorCharacterFromActorInfo()->GetCurrentHook();
		if (CurrentHook)
		{
			UDBDBlueprintFunctionLibrary::AttachCharacterWithRotationAdjust(CurrentHook->GetSkeletalMeshComponent(),
			                                                                FName("socket_KillerAttach"),
			                                                                GetSurvivorCharacterFromActorInfo(),
			                                                                FRotator(0, 90, 0));
		}
	}
	// PredictionKey는 클라이언트가 서버의 명령 없이 예측해서 실행할 때 사용 - 애니메이션 재생 등 중요한 로직이 아닐 경우
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		UAbilityTask_PlayMontageAndWait* PlayStartMontageTask =
			UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
				this, NAME_None, StartInMontage, 1.f);
		PlayStartMontageTask->OnBlendOut.AddDynamic(this, &UGA_SurvivorHookedIn::K2_EndAbility);
		PlayStartMontageTask->OnCancelled.AddDynamic(this, &UGA_SurvivorHookedIn::K2_EndAbility);
		PlayStartMontageTask->OnCompleted.AddDynamic(this, &UGA_SurvivorHookedIn::K2_EndAbility);
		PlayStartMontageTask->OnInterrupted.AddDynamic(this, &UGA_SurvivorHookedIn::K2_EndAbility);
		PlayStartMontageTask->ReadyForActivation();
		GetSurvivorCharacterFromActorInfo()->SetCollisionAndGravityEnabled(false);
	}
}
//
//
// void UGA_SurvivorHookedIn::PlayStartOutMontage()
// {
// 	if (IsActive())
// 	{
// 		AObj_Hook* CurrentHook = GetSurvivorCharacterFromActorInfo()->GetCurrentHook();
// 		if (CurrentHook)
// 		{
// 			UDBDBlueprintFunctionLibrary::AttachCharacterWithRotationAdjust(CurrentHook->GetSkeletalMeshComponent(),
// 																			FName("socket_SurvivorAttach"),
// 																			GetSurvivorCharacterFromActorInfo(),
// 																			FRotator(0, 90, 0));
// 		}
// 		// PredictionKey는 클라이언트가 서버의 명령 없이 예측해서 실행할 때 사용 - 애니메이션 재생 등 중요한 로직이 아닐 경우
// 		if (HasAuthorityOrPredictionKey(GetCurrentActorInfo(), &GetCurrentActivationInfoRef()))
// 		{
// 			UAbilityTask_PlayMontageAndWait* PlayStartMontageTask =
// 				UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
// 					this, NAME_None, StartOutMontage, 1.f);
// 			PlayStartMontageTask->OnBlendOut.AddDynamic(this, &UGA_SurvivorHookedIn::K2_EndAbility);
// 			PlayStartMontageTask->OnCancelled.AddDynamic(this, &UGA_SurvivorHookedIn::K2_EndAbility);
// 			PlayStartMontageTask->OnCompleted.AddDynamic(this, &UGA_SurvivorHookedIn::K2_EndAbility);
// 			PlayStartMontageTask->OnInterrupted.AddDynamic(this, &UGA_SurvivorHookedIn::K2_EndAbility);
// 			PlayStartMontageTask->ReadyForActivation();
// 			GetSurvivorCharacterFromActorInfo()->SetCollisionAndGravityEnabled(false);
// 		}
// 	}
// }

void UGA_SurvivorHookedIn::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo,
                                      const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                                      bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if (GetAnimInstance())
	{
		GetAnimInstance()->StopAllMontages(0.1f);
	}
	if (bWasCancelled)
	{
		GetSurvivorCharacterFromActorInfo()->SetCollisionAndGravityEnabled(true);
		return;
	}
	// if (K2_HasAuthority())
	// {
	// 	GetAbilitySystemComponentFromActorInfo()->TryActivateAbilitiesByTag(
	// 		FGameplayTagContainer(DBDGameplayTags::Survivor_Ability_Passive_Hooked));
	// }
}
