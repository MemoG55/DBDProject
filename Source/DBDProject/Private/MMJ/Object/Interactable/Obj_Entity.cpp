// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Interactable/Obj_Entity.h"

#include "MMJ/Object/Component/IC_Entity.h"
#include "MMJ/Object/Component/IC_Hook.h"
#include "MMJ/Object/Interactable/Obj_Hook.h"
#include "Net/UnrealNetwork.h"

AObj_Entity::AObj_Entity(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UIC_Entity>(ADBDObject::InteractableComponentName))
{
	PrimaryActorTick.bCanEverTick = false;

	ObjectStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectStaticMesh"));
	ObjectStaticMesh->SetupAttachment(ObjectMesh);
}

UStaticMeshComponent* AObj_Entity::GetStaticMeshComponent() const
{
	return ObjectStaticMesh;
}


void AObj_Entity::SetActive()
{
	bIsActive = true;
	SetDissolve(0.f);
	ObjectMesh->SetVisibility(bIsActive);
	ObjectStaticMesh->SetVisibility(bIsActive);
}

void AObj_Entity::SetInActive()
{
	bIsActive = false;
	SetDissolve(0.f);
	ObjectMesh->SetVisibility(bIsActive);
	ObjectStaticMesh->SetVisibility(bIsActive);
}

void AObj_Entity::SetDissolve(float Percent)
{
	DissolveAmount = (Percent) * 6.f;
	//DissolveAmount = FMath::Clamp(MaxDissolveAmount * (1.f - Percent), 0.f, MaxDissolveAmount);
}

void AObj_Entity::OnRep_DissolveAmount()
{
	ObjectMesh->SetScalarParameterValueOnMaterials(FName("Dissolve Amount"), DissolveAmount);
	ObjectStaticMesh->SetScalarParameterValueOnMaterials(FName("Dissolve Amount"), DissolveAmount);
}

void AObj_Entity::OnRep_IsActive()
{
	ObjectMesh->SetVisibility(bIsActive);
	ObjectStaticMesh->SetVisibility(bIsActive);
}

void AObj_Entity::BeginPlay()
{
	Super::BeginPlay();

	ObjectMesh->SetVisibility(false);
	ObjectStaticMesh->SetVisibility(false);

	if (GetOwner())
	{
		if (ADBDObject* OwnerObj = Cast<ADBDObject>(GetOwner()))
		{
			OwnerObject = OwnerObj;
			if (UICObject* OwnerIC = Cast<UICObject>(OwnerObj->GetInteractableComponent()))
			{
				OwnerObjIC = OwnerIC;
			}
		}
	}
}

void AObj_Entity::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

void AObj_Entity::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(AObj_Entity, bIsActive, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AObj_Entity, DissolveAmount, COND_None, REPNOTIFY_Always);
}

