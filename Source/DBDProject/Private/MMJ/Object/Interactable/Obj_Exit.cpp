// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Interactable/Obj_Exit.h"

#include "MMJ/Object/Component/ICExitDoor.h"

AObj_Exit::AObj_Exit(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UICExitDoor>(ADBDObject::InteractableComponentName))
{
	
}
