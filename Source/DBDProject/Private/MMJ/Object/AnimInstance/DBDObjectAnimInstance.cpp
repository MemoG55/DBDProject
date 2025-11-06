// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/AnimInstance/DBDObjectAnimInstance.h"

#include "MMJ/Object/Component/ICObject.h"
#include "MMJ/Object/GAS/ObjAttributeSet.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/Component/InteractableComponent.h"

UDBDObjectAnimInstance::UDBDObjectAnimInstance()
{
}

void UDBDObjectAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningObject = Cast<ADBDObject>(GetOwningActor());
	if (IsValid(OwningObject))
	{
		OwningObjectASC = Cast<UObjAbilitySystemComponent>(OwningObject->GetAbilitySystemComponent());
		OwningObjectIC = Cast<UICObject>(OwningObject->GetInteractableComponent());
	}
}


void UDBDObjectAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwningObject)
	{
		// 현재 진행도 연동
		if (OwningObjectASC)
		{
			MaxTask = OwningObjectASC->GetNumericAttribute(UObjAttributeSet::GetMaxTaskAttribute());
			CurrentTask = OwningObjectASC->GetNumericAttribute(UObjAttributeSet::GetCurrentTaskAttribute());
			InteractionProgress = CurrentTask / MaxTask;
		}
		// 상호작용중인 액터 수 (필요 없을 수도?)
		// if (OwningObject->GetInteractableComponent())
		// {
		// 	InteractorsCount = OwningObject->GetInteractableComponent()->GetInteractors().Num();
		// }
	}
}

void UDBDObjectAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	// TODO :: 여기서 MaxTask는 안가져와지는데 혹시 이유가 ??
	if (IsValid(OwningObjectASC))
	{
		MaxTask = OwningObjectASC->GetNumericAttribute(UObjAttributeSet::GetMaxTaskAttribute());
	}
}
