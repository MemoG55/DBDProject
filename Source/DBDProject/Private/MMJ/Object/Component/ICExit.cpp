// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Component/ICExit.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "MMJ/Object/Component/ICExitDoor.h"
#include "MMJ/Object/Interactable/Obj_ExitDoor.h"
#include "Shared/DBDDebugHelper.h"

void UICExit::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	{
		if (OwningObjectASC->HasMatchingGameplayTag(DBDGameplayTags::Object_Status_IsActive)
			&& !OwningObjectASC->GetObjDataAsset()->ActiveAdditionalEffects.IsEmpty())
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

void UICExit::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->GetOwner())
	{
		if (IInteractable* II = Cast<IInteractable>(GetOwner()->GetOwner()))
		{
			if (UICExitDoor* IC = Cast<UICExitDoor>(II->GetInteractableComponent()))
			{
				ExitDoor = Cast<AObj_ExitDoor>(II);
				IC->OnComplete.AddDynamic(this, &ThisClass::SetActivate);
			}
		}
	}
}

void UICExit::SetActivate()
{
	StartInteraction(ExitDoor);
}

