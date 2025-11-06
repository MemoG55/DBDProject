// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Component/IC_Entity.h"

#include "MMJ/Object/Interactable/Obj_Entity.h"

void UIC_Entity::FinishInteraction(AActor* Actor)
{
	Super::FinishInteraction(Actor);

	if (AObj_Entity* OwnerEntity = Cast<AObj_Entity>(OwningObject))
	{
		//OwnerEntity->SetInActive();
	}
}
