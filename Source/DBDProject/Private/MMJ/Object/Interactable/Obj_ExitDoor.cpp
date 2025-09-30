// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Interactable/Obj_ExitDoor.h"

#include "MMJ/Object/Component/ICExitDoor.h"
#include "MMJ/Object/Interactable/Obj_Exit.h"

AObj_ExitDoor::AObj_ExitDoor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UICExitDoor>(ADBDObject::InteractableComponentName))
{
}

void AObj_ExitDoor::BeginPlay()
{
	Super::BeginPlay();

	CreateExitZone();
}

void AObj_ExitDoor::CreateExitZone()
{	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(FVector(0, 0, 0));
		
	ADBDObject* Exit = GetWorld()->SpawnActor<ADBDObject>(ExitZone, SpawnParameters);
	//ADBDObject* Exit = GetWorld()->SpawnActorDeferred<ADBDObject>(ExitZone, SpawnTransform, this);
	if (Exit)
	{
		Exit->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
}
