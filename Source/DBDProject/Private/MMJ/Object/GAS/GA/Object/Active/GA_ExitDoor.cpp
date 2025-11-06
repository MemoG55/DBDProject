// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/GA/Object/Active/GA_ExitDoor.h"

#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "MMJ/Object/Component/ICObject.h"
#include "MMJ/Object/DataAsset/ObjDataAsset.h"
#include "Shared/DBDGameplayTags.h"

UGA_ExitDoor::UGA_ExitDoor()
{
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::OwnedTagPresent;
	TriggerData.TriggerTag = DBDGameplayTags::Object_Status_IsActive;
	AbilityTriggers.Add(TriggerData);
}

void UGA_ExitDoor::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	ObjInteractableComponent->OnInteract.AddDynamic(this, &ThisClass::MontagePlayDelegate);
	ObjInteractableComponent->OnDisconnect.AddDynamic(this, &ThisClass::MontageStopDelegate);
	// 상호작용 취소를 델리게이트로 연결
	ObjInteractableComponent->OnDisconnect.AddDynamic(this, &ThisClass::UnSetTaskTimer);
	
	// Active 활성화 이후 생존자의 애니메이션에서 Object_Event_Interact를 보내야함
	WaitTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this,
		DBDGameplayTags::Object_Event_Interact
		);
	WaitTask->EventReceived.AddDynamic(this, &ThisClass::ExecuteTaskByEvent);
	WaitTask->ReadyForActivation();

	
}

void UGA_ExitDoor::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ObjInteractableComponent->OnDisconnect.RemoveDynamic(this, &ThisClass::UnSetTaskTimer);
	ObjInteractableComponent->OnInteract.RemoveDynamic(this, &ThisClass::MontagePlayDelegate);
	ObjInteractableComponent->OnDisconnect.RemoveDynamic(this, &ThisClass::MontageStopDelegate);
	
	ObjectStopMontage(TaskMontage);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_ExitDoor::TaskFunction()
{
	Super::TaskFunction();

	int32 InteractorCount = ObjInteractableComponent->GetInteractors().Num();
	
	float TaskSpeed = ObjInteractableComponent->GetTaskAttributeOfInteractors();

	FGameplayEffectContextHandle SpecContext = OwningObjectASC->MakeEffectContext();
	SpecContext.AddSourceObject(OwningObject);
	SpecContext.AddInstigator(OwningObject, OwningObject);

	for (const FObjGEStruct& Effect : OwningObjectASC->GetObjDataAsset()->ActiveAdditionalEffects)
	{
		FGameplayEffectSpecHandle SpecHandle = OwningObjectASC->MakeOutgoingSpec(
			Effect.GameplayEffect, 1, SpecContext);
		SpecHandle.Data->SetSetByCallerMagnitude(DBDGameplayTags::Object_Progress_Speed, TaskSpeed);
		SpecHandle.Data->SetSetByCallerMagnitude(DBDGameplayTags::Object_Progress_ActorCount, InteractorCount);
		OwningObjectASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void UGA_ExitDoor::ExecuteTaskByEvent(FGameplayEventData Data)
{
	Super::ExecuteTaskByEvent(Data);

	if (!TaskTimerHandle.IsValid())
	{
		SetTaskTimer();
	}
}

inline void UGA_ExitDoor::MontagePlayDelegate()
{
	if (IsValid(TaskMontage))
	{
		ObjectPlayMontage(TaskMontage);
	}
}

void UGA_ExitDoor::MontageStopDelegate()
{
	if (IsValid(TaskMontage))
	{
		ObjectStopMontage(TaskMontage);
	}
}
