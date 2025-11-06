// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Component/InteractableComponent.h"

#include "MMJ/Object/TestSurvivor.h"
#include "MMJ/Object/GAS/ObjAttributeSet.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDEnum.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Character/DBDCharacter.h"


// Sets default values for this component's properties
UInteractableComponent::UInteractableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	UPrimitiveComponent::SetCollisionProfileName(FName("InteractionOnly"));
	
	
}

void UInteractableComponent::Init()
{
	if (IInteractable* Interactable = Cast<IInteractable>(OwningActor))
	{ 
		OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
		OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);
	}
	OnInteract.RemoveAll(this);
	OnInteractWithActor.RemoveAll(this);
	OnDisconnect.RemoveAll(this);
	OnDisconnectWithActor.RemoveAll(this);
	OnComplete.RemoveAll(this);
	OnCompleteWithActor.RemoveAll(this);
	OnDestroy.RemoveAll(this);
	OnDestroyWithActor.RemoveAll(this);
	
	OnInteract.AddDynamic(this, &ThisClass::OnInteracted);
	OnInteractWithActor.AddDynamic(this, &ThisClass::OnInteractedWithActor);
	OnDisconnect.AddDynamic(this, &ThisClass::OnDisconnected);
	OnDisconnectWithActor.AddDynamic(this, &ThisClass::OnDisconnectedWithActor);
	OnComplete.AddDynamic(this, &ThisClass::OnCompleted);
	OnCompleteWithActor.AddDynamic(this, &ThisClass::OnCompletedWithActor);
	OnDestroy.AddDynamic(this, &ThisClass::OnDestroyed);
	OnDestroyWithActor.AddDynamic(this, &ThisClass::OnDestroyedWithActor);
}

bool UInteractableComponent::CheckAuthority() const
{
	return OwningActor && OwningActor->HasAuthority() && OwningASC;
}


void UInteractableComponent::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO :: IMC 전달
	if (IInteractable* ASI = Cast<IInteractable>(OtherActor))
	{
		if (ATestSurvivor* Character = Cast<ATestSurvivor>(OtherActor))
		{
			Character->SetCanInteract(true);
		}
	}
}

void UInteractableComponent::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(OtherActor))
	{
		if (ATestSurvivor* Character = Cast<ATestSurvivor>(OtherActor))
		{
			Character->SetCanInteract(false);
		}
	}
}

// Called when the game starts
void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (!OwningActor)
	{
		OwningActor = GetOwner();
	}
	if (IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(OwningActor))
	{
		OwningASC = Cast<UDBDAbilitySystemComponent>(ASI->GetAbilitySystemComponent());
	}
	
	Init();
}

void UInteractableComponent::StartInteraction(AActor* Actor)
{
	if (!CheckAuthority()) return;
}

void UInteractableComponent::TickInteraction(AActor* Actor)
{
	if (!CheckAuthority()) return;
}

void UInteractableComponent::FinishInteraction(AActor* Actor)
{
	if (!CheckAuthority()) return;
}

void UInteractableComponent::CompleteInteraction(AActor* Actor)
{
	if (!CheckAuthority()) return;
}

void UInteractableComponent::DestroyInteraction(AActor* Actor)
{
	if (!CheckAuthority()) return;
}

bool UInteractableComponent::CanInteraction(AActor* Actor)
{
	if (!CheckAuthority()) return false;
	return true;
}

TArray<AActor*> UInteractableComponent::GetInteractors()
{
	return InteractedActors;
}

void UInteractableComponent::SetInteractors(AActor* Actor)
{
	if (!CheckAuthority()) return;

	if (!Actor) return;
	
	if (!InteractedActors.Contains(Actor))
	{
		InteractedActors.Add(Actor);

		CachedCurrentInteractor = Actor;
		
		OnInteract.Broadcast();
		OnInteractSourceObject.Broadcast(OwningActor);
		if (ADBDCharacter* Character = Cast<ADBDCharacter>(Actor))
		{
			OnInteractWithActor.Broadcast(Actor);
			OnInteractInfo.Broadcast(OwningActor, Actor);
		}
	}
}

void UInteractableComponent::UnSetInteractors(AActor* Actor)
{
	if (!CheckAuthority()) return;

	if (!Actor) return;

	if (InteractedActors.Contains(Actor))
	{
		InteractedActors.RemoveAll([Actor](const AActor* InteractedActor){ return InteractedActor == Actor; });

		if (InteractedActors.Num() > 0)
		{
			CachedCurrentInteractor = InteractedActors.Last();
		}
		else
		{
			CachedCurrentInteractor = nullptr;
		}
		
		OnDisconnect.Broadcast();
		OnDisconnectSourceObject.Broadcast(OwningActor);
		if (ADBDCharacter* Character = Cast<ADBDCharacter>(Actor))
		{
			OnDisconnectWithActor.Broadcast(Actor);
			OnDisconnectInfo.Broadcast(OwningActor, Actor);
		}
	}
}

void UInteractableComponent::BeginInteraction(AActor* Actor)
{
	if (!CheckAuthority()) return;

	if (!Actor) return;

	StartInteraction(Actor);
}

void UInteractableComponent::EndInteraction(AActor* Actor)
{
	if (!CheckAuthority()) return;

	if (!Actor) return;

	FinishInteraction(Actor);
}

float UInteractableComponent::GetTaskAttributeOfInteractors() const
{
	if (!CheckAuthority()) return 0.f;
	
	if (InteractedActors.IsEmpty() || TaskAttribute == nullptr)
	{
		return 0.f;
	}

	// 발전기 로직 예시(자식으로 이동필요)
	float TaskSpeed = 0.f;
	float Efficiency = 1.f - 0.1f * (InteractedActors.Num() - 1);
	
	for (AActor* Actor : InteractedActors)
	{
		if (ADBDCharacter* Character = Cast<ADBDCharacter>(Actor))
		{
			if (UDBDAbilitySystemComponent* ASC = Cast<UDBDAbilitySystemComponent>(Character->GetAbilitySystemComponent()))
			{
				// 계산로직
				// 각 태스크속도를 오브젝트마다 변수로 설정해서? 할 수 있을까?
				float CurrentActorTaskSpeed = ASC->GetNumericAttribute(TaskAttribute);
				
				// TODO :: 퍽에 의한 것으로 전역적으로 적용된 퍽에 한해 가져옴
				// float PerkBonus = ASC->GetNumericAttribute(TaskSpeedAttribute);
				float PerkBonus = 1.0f;
				TaskSpeed += (CurrentActorTaskSpeed * Efficiency * PerkBonus);
			}
		}
	}

	return TaskSpeed;
}

float UInteractableComponent::GetInteractionProgress()
{
	/*
	if (OwningASC)
	{
		bool bFound = false;
		float CurrentTask = OwningASC->GetGameplayAttributeValue(OwningActor->ObjAttributeSet->GetCurrentTaskAttribute(), bFound);
		float MaxTask = OwningASC->GetGameplayAttributeValue(OwningActor->ObjAttributeSet->GetMaxTaskAttribute(), bFound);
		if (bFound && CurrentTask >= MaxTask)
		{
			return CurrentTask / MaxTask;
		}
	}*/
	return 0.f;
}

float UInteractableComponent::GetInteractionDuration(AActor* Actor)
{
	return 0.0f;
}

void UInteractableComponent::SetTaskAttribute(FGameplayAttribute GameplayAttribute)
{
	if (!CheckAuthority()) return;
	
	if (GameplayAttribute.IsValid())
	{
		TaskAttribute = GameplayAttribute;
	}
}

void UInteractableComponent::SetInteractorLocation(AActor* Actor)
{
	if (!CheckAuthority()) return;
	
	if (!Actor) return;
}

void UInteractableComponent::UnSetInteractorLocation(AActor* Actor)
{
	if (!CheckAuthority()) return;

	if (!Actor) return;
}

void UInteractableComponent::OnInteracted_Implementation()
{
	if (!CheckAuthority()) return;
}

void UInteractableComponent::OnInteractedWithActor_Implementation(AActor* Actor)
{
	if (!CheckAuthority()) return;
	
	if (!Actor) return;
}

void UInteractableComponent::OnDisconnected_Implementation()
{
	if (!CheckAuthority()) return;
}

void UInteractableComponent::OnDisconnectedWithActor_Implementation(AActor* Actor)
{
	if (!CheckAuthority()) return;
	
	if (!Actor) return;
}

void UInteractableComponent::OnCompleted_Implementation()
{
	if (!CheckAuthority()) return;
}

void UInteractableComponent::OnCompletedWithActor_Implementation(AActor* Actor)
{
	if (!CheckAuthority()) return;

	if (!Actor) return;
}


void UInteractableComponent::OnDestroyed_Implementation()
{
	if (!CheckAuthority()) return;
}

void UInteractableComponent::OnDestroyedWithActor_Implementation(AActor* Actor)
{
	if (!CheckAuthority()) return;

	if (!Actor) return;
}

bool UInteractableComponent::IsActivate()
{
	return UDBDBlueprintFunctionLibrary::NativeActorHasTag(OwningActor, DBDGameplayTags::Object_Status_IsActive);
}

bool UInteractableComponent::IsComplete()
{
	return UDBDBlueprintFunctionLibrary::NativeActorHasTag(OwningActor, DBDGameplayTags::Object_Status_IsComplete);
}

bool UInteractableComponent::IsDestroy()
{
	return UDBDBlueprintFunctionLibrary::NativeActorHasTag(OwningActor, DBDGameplayTags::Object_Status_IsDestroy);
}