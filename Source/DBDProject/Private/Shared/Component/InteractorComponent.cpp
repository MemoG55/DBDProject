// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Component/InteractorComponent.h"

#include "EnhancedInputSubsystems.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/Component/InteractableComponent.h"
#include "Shared/Interface/Interactable.h"
#include "Shared/Interface/Interactor.h"


// Sets default values for this component's properties
UInteractorComponent::UInteractorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SphereRadius = 150.f;
	SetIsReplicatedByDefault(true);
	SetCollisionProfileName(FName("NoCollision"));

	bIsSearchingEnabled = true;
	SearchInterval = 0.1f;
	SearchRadius = 150.f;
}


// Called when the game starts
void UInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimer(SearchTimerHandle, this, &UInteractorComponent::CheckNearbyInteractable,
		                                       SearchInterval, true);
	}
}

void UInteractorComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInteractorComponent::CheckNearbyInteractable()
{
	if (!bIsSearchingEnabled)
	{
		return;
	}
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	TArray<FHitResult> HitResults;
	ETraceTypeQuery TraceTypeQuery = UCollisionProfile::Get()->ConvertToTraceType(
		ECollisionChannel::ECC_GameTraceChannel2);
	UKismetSystemLibrary::SphereTraceMulti(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation(),
	                                       SearchRadius,
	                                       TraceTypeQuery, false, ActorsToIgnore, EDrawDebugTrace::Type::ForDuration,
	                                       HitResults, true, FLinearColor::Red, FLinearColor::Green, 0.1);

	AActor* ClosestActor = nullptr;
	float ClosestDistance = MAX_FLT;
	if (HitResults.Num() == 0)
	{
		RegisterOverlappedInteractable(nullptr);
		return;
	}
	for (const FHitResult& HitResult : HitResults)
	{
		IInteractable* Interactable = Cast<IInteractable>(HitResult.GetActor());
		if (Interactable && Interactable->GetInteractableComponent()->CanInteraction(GetOwner()))
		{
			FVector HitActorLocation = HitResult.GetActor()->GetActorLocation();
			FVector OwnerLocation = GetOwner()->GetActorLocation();
			float DistanceToActor = (HitActorLocation - OwnerLocation).Size();
			if (DistanceToActor < ClosestDistance)
			{
				RegisterOverlappedInteractable(Interactable);
				ClosestDistance = DistanceToActor;
			}
		}
	}
	// HitResult는 있으나 Interactable이 없는 경우
	if (ClosestDistance == MAX_FLT)
	{
		RegisterOverlappedInteractable(nullptr);
	}
}

void UInteractorComponent::RegisterOverlappedInteractable(IInteractable* Interactable)
{
	CurrentInteractable = Interactable;
	// JMS: 서버에서만 실행되므로 단순화했습니다.
	AActor* NewInteractableActor = CurrentInteractable
		                               ? CurrentInteractable->GetInteractableComponent()->GetOwner()
		                               : nullptr;
	CurrentInteractableActor = NewInteractableActor;

	UpdateTag();
}


void UInteractorComponent::UnRegisterOverlappedInteractable(IInteractable* Interactable)
{
	if (CurrentInteractable == Interactable)
	{
		CurrentInteractable = nullptr;
		UpdateTag();
	}
}


void UInteractorComponent::InteractWithCurrentInteractable()
{
	if (CurrentInteractable)
	{
		if (CurrentInteractable->GetInteractableComponent()->CanInteraction(GetOwner()))
		{
			// Getter를 호출해서 컴포넌트를 가져옴
			// Interact delegate Broadcast : MMJ (OnInteractWithActor 델리게이트 호출에서 일반 함수 호출로 변경)
			CurrentInteractable->GetInteractableComponent()->BeginInteraction(GetOwner());
		}
	}
	SearchingEnabled(false);
}

void UInteractorComponent::EndInteraction()
{
	//현재 Interactable의 Interaction마무리 delegate broadcast
	if (CurrentInteractable)
	{
		//  MMJ (OnDisconnectWithActor 델리게이트 호출에서 일반 함수 호출로 변경)
		CurrentInteractable->GetInteractableComponent()->EndInteraction(GetOwner());
	}
	SearchingEnabled(true);
}

void UInteractorComponent::SearchingEnabled(bool bEnabled)
{
	bIsSearchingEnabled = bEnabled;
}

IInteractor* UInteractorComponent::GetOwnerAsInteractor()
{
	return Cast<IInteractor>(GetOwner());
}

UAbilitySystemComponent* UInteractorComponent::GetOwnerAbilitySystemComponent()
{
	IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(GetOwner());
	if (!ASI)
	{
		return nullptr;
	}
	return ASI->GetAbilitySystemComponent();
}

void UInteractorComponent::UpdateTag()
{
	UDBDBlueprintFunctionLibrary::RemoveAllSubTags(FName("Interactable"), GetOwnerAbilitySystemComponent());
	if (CurrentInteractable)
	{
		GetOwnerAbilitySystemComponent()->AddLooseGameplayTag(
			CurrentInteractable->GetInteractableComponent()->InteractableTag);
		GetOwnerAbilitySystemComponent()->AddReplicatedLooseGameplayTag(
			CurrentInteractable->GetInteractableComponent()->InteractableTag);
	}
}

void UInteractorComponent::OnRep_CurrentInteractableActor()
{
}

void UInteractorComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UInteractorComponent, CurrentInteractableActor, COND_None, REPNOTIFY_Always);
}


AActor* UInteractorComponent::GetCurrentInteractableActor()
{
	return CurrentInteractableActor;
}

#if WITH_EDITOR
void UInteractorComponent::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	FName PropertyName = (PropertyChangedEvent.Property != nullptr)
		                     ? PropertyChangedEvent.Property->GetFName()
		                     : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UInteractorComponent, SearchRadius))
	{
		SetSphereRadius(SearchRadius);
	}
}
#endif
