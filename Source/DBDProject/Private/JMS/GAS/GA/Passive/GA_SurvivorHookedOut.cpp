// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/GAS/GA/Passive/GA_SurvivorHookedOut.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MMJ/Object/Interactable/Obj_Hook.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDGameplayTags.h"


UGA_SurvivorHookedOut::UGA_SurvivorHookedOut()
{
	AbilityTags.AddTag(DBDGameplayTags::Survivor_Ability_Passive_Hooked);
	ActivationOwnedTags.AddTag(DBDGameplayTags::Survivor_Status_MoveDisabled);
	
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::OwnedTagPresent;
	TriggerData.TriggerTag = DBDGameplayTags::Survivor_Status_Hooked;
	AbilityTriggers.Add(TriggerData);
}

void UGA_SurvivorHookedOut::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
		Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!ASC)
	{
		return;
	}
	if (K2_HasAuthority())
	{
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
		TArray<AActor*> OutActors;
		UKismetSystemLibrary::SphereOverlapActors(GetAvatarActorFromActorInfo(),
		                                          GetAvatarActorFromActorInfo()->GetActorLocation(), 500.f, ObjectTypes,
		                                          AObj_Hook::StaticClass(), ActorsToIgnore, OutActors);
		DrawDebugSphere(GetWorld(), GetAvatarActorFromActorInfo()->GetActorLocation(), 500.f, 10, FColor::Red, true);
		if (OutActors.IsEmpty())
		{
			Debug::Print(TEXT("JMS11: UGA_SurvivorHooked : No HookClass Nearby"), 11);
			K2_EndAbility();
			return;
		}

		CachedHook = Cast<AObj_Hook>(OutActors.Top());
		if (!CachedHook)
		{
			Debug::Print(TEXT("JMS12: UGA_SurvivorHooked : No HookInstance Nearby"), 12);
			K2_EndAbility();
			return;
		}
		UDBDBlueprintFunctionLibrary::AttachCharacterWithRotationAdjust(CachedHook->GetSkeletalMeshComponent(),
		                                                                FName("socket_SurvivorAttach"),
		                                                                GetSurvivorCharacterFromActorInfo(),
		                                                                FRotator(0, 90, 0));
	}
	// PredictionKey는 클라이언트가 서버의 명령 없이 예측해서 실행할 때 사용 - 애니메이션 재생 등 중요한 로직이 아닐 경우
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		UAbilityTask_PlayMontageAndWait* PlayStartMontageTask =
			UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
				this, NAME_None, StartOutMontage, 1.f);
		PlayStartMontageTask->OnBlendOut.AddDynamic(this, &UGA_SurvivorHookedOut::K2_EndAbility);
		PlayStartMontageTask->OnCancelled.AddDynamic(this, &UGA_SurvivorHookedOut::K2_EndAbility);
		PlayStartMontageTask->OnCompleted.AddDynamic(this, &UGA_SurvivorHookedOut::K2_EndAbility);
		PlayStartMontageTask->OnInterrupted.AddDynamic(this, &UGA_SurvivorHookedOut::K2_EndAbility);
		PlayStartMontageTask->ReadyForActivation();
		GetSurvivorCharacterFromActorInfo()->SetCollisionAndGravityEnabled(false);
	}
}

void UGA_SurvivorHookedOut::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
