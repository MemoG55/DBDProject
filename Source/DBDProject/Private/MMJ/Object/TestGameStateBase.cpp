// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/TestGameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "MMJ/Object/DBDObject.h"
#include "MMJ/Object/GAS/ObjAbilitySystemComponent.h"
#include "MMJ/Object/Interactable/Obj_ExitDoor.h"
#include "MMJ/Object/Interactable/Obj_Generator.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDGameplayTags.h"

ATestGameStateBase::ATestGameStateBase()
{
	bReplicates = true;
	
}


void ATestGameStateBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ATestGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		// 발전기
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AObj_Generator::StaticClass(), FoundActors);
		for (AActor* Actor : FoundActors)
		{
			if (AObj_Generator* Object = Cast<AObj_Generator>(Actor))
			{
				Generators.Add(Object);

				Object->OnComplete.AddDynamic(this, &ThisClass::ATestGameStateBase::CheckGeneratorState);
			}
		}
		// 탈출구
		FoundActors.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AObj_ExitDoor::StaticClass(), FoundActors);
		for (AActor* Actor : FoundActors)
		{
			if (AObj_ExitDoor* Object = Cast<AObj_ExitDoor>(Actor))
			{
				ExitDoors.Add(Object);
			}
		}
	}
}

void ATestGameStateBase::GetRequiredGeneratorCount()
{
	// 플레이어 생존자 수 구하기
	
}

void ATestGameStateBase::CheckGeneratorState()
{
	if (!HasAuthority()) return;
	int32 RepairCount = 0;
	for (ADBDObject* Generator : Generators)
	{
		if (UDBDBlueprintFunctionLibrary::NativeActorHasTag(Generator, DBDGameplayTags::Object_Status_IsComplete))
		{
			RepairCount++;
		}
	}

	if (RepairCount >= 3)
	{
		for (ADBDObject* ExitDoor : ExitDoors)
		{
			ExitDoor->SetCanActive(true);
		}
	}
}
