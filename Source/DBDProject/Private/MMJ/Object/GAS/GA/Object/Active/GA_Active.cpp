// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/GA/Object/Active/GA_Active.h"

#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "MMJ/Object/Component/ICObject.h"
#include "MMJ/Object/GAS/ObjAttributeSet.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/Controller/DBDPlayerController.h"

void UGA_Active::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// 위젯이 필요한 오브젝트의 경우를 위해 위젯을 바인딩하는 함수를 연결
	if (bUseWidget)
	{
		ObjInteractableComponent->OnInteractWithActor.AddDynamic(this, &ThisClass::SetWidget);
		ObjInteractableComponent->OnDisconnectWithActor.AddDynamic(this, &ThisClass::UnSetWidget);
	}
	
	if (!bAutoActive)
	{
		if (ActiveTag.IsValid())
		{
			WaitTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
				this,
				ActiveTag
				);
			WaitTask->EventReceived.AddDynamic(this, &ThisClass::ExecuteTaskByEvent);
			WaitTask->ReadyForActivation();
		}
	}
	else
	{
		ExecuteTaskByEvent(FGameplayEventData());
	}
}

void UGA_Active::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                            const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	UnSetTaskTimer();
	if (bUseWidget)
	{
		ObjInteractableComponent->OnInteractWithActor.RemoveDynamic(this, &ThisClass::SetWidget);
		ObjInteractableComponent->OnDisconnectWithActor.RemoveDynamic(this, &ThisClass::UnSetWidget);

		// 완료되었을 시 에는 모든 인터랙터에 UI를 해제
		if (OwningObjectASC->IsMaxTask())
		{
			for (AActor* Actor : ObjInteractableComponent->GetInteractors())
			{
				if (ADBDCharacter* Character = Cast<ADBDCharacter>(Actor))
				{
					if (ADBDPlayerController* PC = Cast<ADBDPlayerController>(Character->GetController()))
					{
						PC->DisplayProgressUI(nullptr);
					}
				}
			}
		}
	}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_Active::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                               const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}



void UGA_Active::SetTaskTimer()
{
	if (!TaskTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(
			TaskTimerHandle,
			this,
			&ThisClass::TaskFunction,
			TaskInterval,
			TaskLoop
		);

		if (ObjInteractableComponent->GetInteractors().Num() > 0 && bUseWidget)
		{
			for (AActor* Actor : ObjInteractableComponent->GetInteractors())
			{
				if (ADBDCharacter* Character = Cast<ADBDCharacter>(Actor))
				{
					if (ADBDPlayerController* PC = Cast<ADBDPlayerController>(Character->GetController()))
					{
						PC->DisplayProgressUI(OwningObjectASC);
					}
				}
			}
		}
	}
}

void UGA_Active::UnSetTaskTimer()
{
	if (TaskTimerHandle.IsValid())
	{
		if (ObjInteractableComponent->GetInteractors().Num() > 0) return;
		
		GetWorld()->GetTimerManager().ClearTimer(TaskTimerHandle);
		TaskTimerHandle.Invalidate();
	}
}

void UGA_Active::TaskFunction()
{
	if (OwningObjectASC->IsMaxTask())
	{
		K2_EndAbility();
		return;
	}
}

void UGA_Active::SetWidget(AActor* Actor)
{
	if (ADBDCharacter* Character = Cast<ADBDCharacter>(Actor))
	{
		if (ADBDPlayerController* PC = Cast<ADBDPlayerController>(Character->GetController()))
		{
			PC->DisplayProgressUI(OwningObjectASC);
		}
	}
}

void UGA_Active::UnSetWidget(AActor* Actor)
{
	if (ADBDCharacter* Character = Cast<ADBDCharacter>(Actor))
	{
		if (ADBDPlayerController* PC = Cast<ADBDPlayerController>(Character->GetController()))
		{
			PC->DisplayProgressUI(nullptr);
		}
	}
}

