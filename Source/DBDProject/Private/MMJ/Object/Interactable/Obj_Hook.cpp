// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Interactable/Obj_Hook.h"

AObj_Hook::AObj_Hook(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UICHook>(ADBDObject::InteractableComponentName))
{
	HookInteractableComponent = Cast<UICHook>(InteractableComponent);
}

UICHook* AObj_Hook::GetInteractableComponent() const
{
	return HookInteractableComponent;
}
