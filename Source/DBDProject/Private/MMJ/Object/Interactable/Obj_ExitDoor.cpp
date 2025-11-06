// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Interactable/Obj_ExitDoor.h"

#include "Components/WidgetComponent.h"
#include "MMJ/Object/Component/IC_ExitDoor.h"
#include "MMJ/Object/Interactable/Obj_Exit.h"
#include "Shared/DBDEnum.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/Subsystem/DBDObjectObserver.h"

AObj_ExitDoor::AObj_ExitDoor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UIC_ExitDoor>(ADBDObject::InteractableComponentName))
{
}

void AObj_ExitDoor::BeginPlay()
{
	Super::BeginPlay();

	if (UDBDObjectObserver* ObjectObserver = GetWorld()->GetSubsystem<UDBDObjectObserver>())
	{
		ObjectObserver->RegisterExitDoor(this);
	}
	if (WidgetComponent)
	{
		WidgetComponent->SetVisibility(false);
	}
	CreateCombinedActor();

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController<APlayerController>())
	{
		if (ADBDPlayerState* PS = PC->GetPlayerState<ADBDPlayerState>())
		{
			if (PS->GetPlayerRole() == EPlayerRole::Killer)
			{
				SetCustomDepth(1);
			}
			else
			{
				SetCustomDepth(2);
			}
		}
	}
}


void AObj_ExitDoor::CreateCombinedActor()
{
	if (IsValid(CombinedActorClass))
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		
		if (ADBDObject* Exit = GetWorld()->SpawnActor<ADBDObject>(CombinedActorClass, SpawnParameters))
		{
			Exit->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			CombinedActor = Exit;
		}
	}
}

AActor* AObj_ExitDoor::GetCombinedActor() const
{
	return CombinedActor;
}
