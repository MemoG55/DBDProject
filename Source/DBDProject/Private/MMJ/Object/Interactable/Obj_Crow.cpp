// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Interactable/Obj_Crow.h"

#include "MMJ/Object/Component/IC_Crow.h"

AObj_Crow::AObj_Crow(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UIC_Crow>(ADBDObject::InteractableComponentName))
{
}
