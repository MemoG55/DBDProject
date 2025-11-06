// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Component/IC_Exit.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "MMJ/Object/Component/IC_ExitDoor.h"
#include "MMJ/Object/Interactable/Obj_Entity.h"
#include "MMJ/Object/Interactable/Obj_ExitDoor.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDDebugHelper.h"

void UIC_Exit::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UDBDBlueprintFunctionLibrary::IsSurvivor(OtherActor))
	{
		if (OwningObjectASC->HasMatchingGameplayTag(DBDGameplayTags::Object_Status_IsActive)
			&& !OwningObjectASC->GetObjDataAsset()->ActiveAdditionalEffects.IsEmpty())
		{
			if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
			{
				for (const FObjGEStruct& GEStruct : OwningObjectASC->GetObjDataAsset()->ActiveAdditionalEffects)
				{
					FGameplayEffectContextHandle ContextHandle = OwningObjectASC->MakeEffectContext();
					FGameplayEffectSpecHandle SpecHandle = OwningObjectASC->MakeOutgoingSpec(GEStruct.GameplayEffect, 1, ContextHandle);
					OwningObjectASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), ASC);
				}
			}
		}
	}
	if (UDBDBlueprintFunctionLibrary::IsKiller(OtherActor))
	{
		if (OwningObject->GetEntity())
		{
			OwningObject->GetEntity()->SetActive();
		}
	}
}

void UIC_Exit::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnCollisionBoxEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	if (UDBDBlueprintFunctionLibrary::IsKiller(OtherActor))
	{
		if (OwningObject->GetEntity())
		{
			OwningObject->GetEntity()->SetInActive();
		}
	}
}

void UIC_Exit::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->GetOwner())
	{
		if (IInteractable* II = Cast<IInteractable>(GetOwner()->GetOwner()))
		{
			if (UIC_ExitDoor* IC = Cast<UIC_ExitDoor>(II->GetInteractableComponent()))
			{
				ExitDoor = Cast<AObj_ExitDoor>(II);
				IC->OnComplete.AddDynamic(this, &ThisClass::SetActivate);
			}
		}
	}
}

void UIC_Exit::SetActivate()
{
	StartInteraction(ExitDoor);
}

