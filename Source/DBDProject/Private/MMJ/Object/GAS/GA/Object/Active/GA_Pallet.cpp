// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/GA/Object/Active/GA_Pallet.h"

#include "MMJ/Object/Component/ICObject.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"

UGA_Pallet::UGA_Pallet()
{
}

void UGA_Pallet::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// TODO :: 퍽으로 판자를 밀어 올릴 수 있는 조건을 찾아야함
	if (IsValid(ObjInteractableComponent->CachedCurrentInteractor))
	{
		//if (UDBDBlueprintFunctionLibrary::NativeActorHasTag(ObjInteractableComponent->CachedCurrentInteractor, DBDGameplayTags::))
		if (IsValid(FallGroundMontage))
		{
			TaskMontage = FallGroundMontage;
		}
	}

	ObjectPlayMontage();
}