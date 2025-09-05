// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Interactable/Obj_Generator.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "JMS/GAS/SurvivorAttributeSet.h"
#include "MMJ/Object/ObjFunctionLibrary.h"
#include "MMJ/Object/DataAsset/ObjDataAsset.h"
#include "MMJ/Object/GAS/ObjAbilitySystemComponent.h"
#include "Shared/DBDGameplayTags.h"

AObj_Generator::AObj_Generator()
{
	
}

void AObj_Generator::StartInteraction(AActor* Actor)
{
	Super::StartInteraction(Actor);
	
	// 액터와의 방향계산해서 적절한 위치로 이동시킴
	FGameplayTag DirectionTag = UObjFunctionLibrary::ComputeInteractDirection(this, Actor);

	FVector Location = GetActorLocation();
	FName SocketName = "joint_CamperAttach01";

	if (DirectionTag == DBDGameplayTags::Shared_Direction_Left)
	{
		Location -= GetActorRightVector() * 150;
		SocketName = "joint_CamperAttach04";
	}
	else if (DirectionTag == DBDGameplayTags::Shared_Direction_Right)
	{
		Location += GetActorRightVector() * 150;
		SocketName = "joint_CamperAttach03";
	}
	else if (DirectionTag == DBDGameplayTags::Shared_Direction_Front)
	{
		Location += GetActorForwardVector() * 150;
		SocketName = "joint_CamperAttach01";
	}
	else if (DirectionTag == DBDGameplayTags::Shared_Direction_Back)
	{
		Location -= GetActorForwardVector() * 150;
		SocketName = "joint_CamperAttach02";
	}

	UE_LOG(LogTemp, Warning, TEXT("MMJ : StartInteraction & Direction %s"), *DirectionTag.ToString())
	Actor->SetActorLocation(Location);
}

void AObj_Generator::TickInteraction(AActor* Actor)
{
	Super::TickInteraction(Actor);

	
}

float AObj_Generator::GetTaskSpeedOfInteractors() const
{
	float TaskSpeed = 0.f;
	if (!InteractedActors.IsEmpty())
	{
		for (AActor* InteractedActor : InteractedActors)
		{
			if (IAbilitySystemInterface* Actor = Cast<IAbilitySystemInterface>(InteractedActor))
			{
				if (UAbilitySystemComponent* ASC = Actor->GetAbilitySystemComponent())
				{
					bool bFound = false;
					float CurrentTaskSpeed = ASC->GetGameplayAttributeValue(USurvivorAttributeSet::GetGeneratorRepairSpeedAttribute(), bFound);
					if (bFound)
					{
						TaskSpeed += CurrentTaskSpeed;
					}
				}
			}
		}
	}
	return TaskSpeed;
}

void AObj_Generator::BeginPlay()
{
	Super::BeginPlay();

	if (ObjAbilitySystemComponent)
	{
		//ObjAbilitySystemComponent->RegisterGameplayTagEvent(DBDGameplayTags::Object_Status_IsDestroy, EGameplayTagEventType::NewOrRemoved).AddUObject(this, )
	}
}