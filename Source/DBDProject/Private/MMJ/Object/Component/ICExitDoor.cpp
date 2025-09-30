// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Component/ICExitDoor.h"

#include "Shared/GameFramework/DBDGameStateBase.h"
#include "MMJ/Object/Component/ICExit.h"
#include "MMJ/Object/Interactable/Obj_Exit.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"

UICExitDoor::UICExitDoor()
{
}

void UICExitDoor::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// GameState에서 CheckGenerate든 뭐든 변수 가져와서 조건걸기
	if (true)
	{
		Super::OnCollisionBoxBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}

void UICExitDoor::StartInteraction(AActor* Actor)
{
	Super::StartInteraction(Actor);

	SetInteractorLocation(Actor);
}

void UICExitDoor::TickInteraction(AActor* Actor)
{
	Super::TickInteraction(Actor);
	
	float TaskSpeed = GetTaskAttributeOfInteractors();
	FGameplayEffectContextHandle SpecContext = OwningObjectASC->MakeEffectContext();
	SpecContext.AddSourceObject(OwningObject);
	SpecContext.AddInstigator(OwningObject, OwningObject);

	if (OwningObjectASC->GetObjDataAsset()->ActiveAdditionalEffects.Num() && OwningObjectASC->GetObjDataAsset()->ActiveAdditionalEffects[0].GameplayEffect)
	{
		// TODO :: Effect는 별도로 지정해야 할 듯?
		FGameplayEffectSpecHandle SpecHandle = OwningObjectASC->MakeOutgoingSpec(
			OwningObjectASC->GetObjDataAsset()->ActiveAdditionalEffects[0].GameplayEffect, 1, SpecContext);
		SpecHandle.Data->SetSetByCallerMagnitude(DBDGameplayTags::Object_Progress_Speed, TaskSpeed);
		SpecHandle.Data->SetSetByCallerMagnitude(DBDGameplayTags::Object_Progress_ActorCount, GetInteractors().Num());
		OwningObjectASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void UICExitDoor::UnSetInteractors(AActor* Actor)
{
	Super::UnSetInteractors(Actor);

	UnSetInteractorLocation(Actor);
}

void UICExitDoor::OnCompleted_Implementation()
{
	Super::OnCompleted_Implementation();
}

bool UICExitDoor::CanInteraction(AActor* Actor)
{
	if (!Super::CanInteraction(Actor))
	{
		return false;
	}
	
	if (UDBDBlueprintFunctionLibrary::IsKiller(Actor))
	{
		return false;
	}

	if (ADBDGameStateBase* GS = Cast<ADBDGameStateBase>(GetWorld()->GetGameState()))
	{
		if (GS->GetRequiredGeneratorCount() > GS->GetRepairGeneratorCount())
		{
			return false;
		}
	}

	return true;
}
