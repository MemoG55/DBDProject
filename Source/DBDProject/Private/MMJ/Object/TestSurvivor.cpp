// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/TestSurvivor.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MMJ/Object/Interactable/DBDObject.h"
#include "Net/UnrealNetwork.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Component/InteractableComponent.h"

APlayerController* ATestSurvivor::GetPlayerController()
{
	return Cast<APlayerController>(GetController());
}

void ATestSurvivor::TryInteract(bool& Result)
{
	//if (!GetController()->IsLocalPlayerController()) return;
	if (!bCanInteract) return;

	TArray<AActor*> AllActors;
	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::SphereTraceMulti(GetWorld(), GetActorLocation(), GetActorLocation(), 150.f,
		TraceTypeQuery1, false, AllActors, EDrawDebugTrace::Type::ForDuration, HitResults, true);

	TSet<AActor*> UniqueActors;
	for (const FHitResult& HitResult : HitResults)
	{
		if (ADBDObject* Obj = Cast<ADBDObject>(HitResult.GetActor()))
		{
			UniqueActors.Add(Obj);
		}
	}
	
	for (AActor* Actor : UniqueActors)
	{
		if (ADBDObject* Obj = Cast<ADBDObject>(Actor))
		{
			Server_Interact(Obj);
			// ServerImplementation 함수에서 실행하는 SetActorRotation 은 복제된 애들만 돌아가고, 클라이언트에서는 적용되지 않는 문제.
			FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Obj->GetActorLocation());
			LookRotation.Pitch = 0;
			//SetActorRotation(LookRotation);
			Result = true;
			//Client_Interact(Obj);
			break;
		}		
	}
	
}


void ATestSurvivor::CancelInteract()
{
	if (CachedCurrentInteractObject)
	{
		Server_Disconnect(CachedCurrentInteractObject);
	}
}

void ATestSurvivor::Client_Interact(ADBDObject* Object)
{
	if (IsValid(Object))
	{
		if (UAbilitySystemComponent* ASC = Object->GetAbilitySystemComponent())
		{
			if (Object->GetInteractableComponent() && Object->GetInteractableComponent()->CanInteraction(this))
			{
				CachedCurrentInteractObject = Object;
				Object->GetInteractableComponent()->BeginInteraction(this);
			}
		}
	}
}

void ATestSurvivor::SetCanInteract(bool Result)
{
	bCanInteract = Result;
}

void ATestSurvivor::GetSurvivor()
{
	
	TArray<AActor*> AllActors;
	TArray<FHitResult> HitResults;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	ObjectType.Add(EObjectTypeQuery::ObjectTypeQuery3);
	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), GetActorLocation(), GetActorLocation(), 150.f, ObjectType, false, AllActors,
		EDrawDebugTrace::ForDuration, HitResults, true);
	//UKismetSystemLibrary::SphereTraceMulti(GetWorld(), GetActorLocation(), GetActorLocation(), 150.f,
		//TraceTypeQuery1, false, AllActors, EDrawDebugTrace::Type::ForDuration, HitResults, true);

	TSet<AActor*> UniqueActors;
	for (const FHitResult& HitResult : HitResults)
	{
		if (ADBDCharacter* Actor = Cast<ADBDCharacter>(HitResult.GetActor()))
		{
			if (Actor != this)
			{
				UniqueActors.Add(Actor);
			}
		}
	}
	
	for (AActor* Actor : UniqueActors)
	{
		SetSurvivor(Cast<ADBDCharacter>(Actor));
		break;
	}
	
}

void ATestSurvivor::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ATestSurvivor::SetSurvivor_Implementation(ADBDCharacter* Actor)
{
	if (!Actor) return;
	Survivor = Actor;
}



void ATestSurvivor::Server_Disconnect_Implementation(ADBDObject* Object)
{
	if (IsValid(Object))
	{
		Object->GetInteractableComponent()->EndInteraction(this);
	}
	CachedCurrentInteractObject = nullptr;
}

void ATestSurvivor::Server_Interact_Implementation(ADBDObject* Object)
{
			//Debug::Print(TEXT("MMJ : InteractTry"), 12);
	if (IsValid(Object))
	{
		if (UAbilitySystemComponent* ASC = Object->GetAbilitySystemComponent())
		{
			if (Object->GetInteractableComponent() && Object->GetInteractableComponent()->CanInteraction(this))
			{
				CachedCurrentInteractObject = Object;
				Object->GetInteractableComponent()->BeginInteraction(this);
			}
		}
	}
}

