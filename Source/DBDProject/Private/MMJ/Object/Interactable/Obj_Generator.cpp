// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Interactable/Obj_Generator.h"

#include "MMJ/Object/Component/ICGenerator.h"


AObj_Generator::AObj_Generator(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UICGenerator>(ADBDObject::InteractableComponentName))
{
	
}

void AObj_Generator::BeginPlay()
{
	Super::BeginPlay();
}

