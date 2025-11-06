// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Component/IC_ExitDoor.h"

#include "Shared/GameFramework/DBDGameStateBase.h"
#include "MMJ/Object/Component/IC_Exit.h"
#include "MMJ/Object/Interactable/Obj_Exit.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"

UIC_ExitDoor::UIC_ExitDoor()
{
	bIsInteractorLocationSet = true;
}

void UIC_ExitDoor::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// GameState에서 CheckGenerate든 뭐든 변수 가져와서 조건걸기
	if (true)
	{
		Super::OnCollisionBoxBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}

bool UIC_ExitDoor::CanInteraction(AActor* Actor)
{
	if (!Super::CanInteraction(Actor))
	{
		return false;
	}

	return true;
}
