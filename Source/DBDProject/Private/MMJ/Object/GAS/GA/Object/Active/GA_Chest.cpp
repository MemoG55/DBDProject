// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/GAS/GA/Object/Active/GA_Chest.h"

#include "MMJ/Object/Component/ICObject.h"
#include "Shared/DBDGameplayTags.h"

UGA_Chest::UGA_Chest()
{
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::OwnedTagPresent;
	TriggerData.TriggerTag = DBDGameplayTags::Object_Status_IsActive;
	AbilityTriggers.Add(TriggerData);
}

void UGA_Chest::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	SetTaskTimer();
}

void UGA_Chest::TaskFunction()
{
	Super::TaskFunction();

	int32 InteractorCount = ObjInteractableComponent->GetInteractors().Num();
	
	float TaskSpeed = ObjInteractableComponent->GetTaskAttributeOfInteractors();

	FGameplayEffectContextHandle SpecContext = OwningObjectASC->MakeEffectContext();
	SpecContext.AddSourceObject(OwningObject);
	SpecContext.AddInstigator(OwningObject, OwningObject);

	for (const FObjGEStruct& Effect : OwningObjectASC->GetObjDataAsset()->ActiveAdditionalEffects)
	{
		FGameplayEffectSpecHandle SpecHandle = OwningObjectASC->MakeOutgoingSpec(
			Effect.GameplayEffect, 1, SpecContext);
		SpecHandle.Data->SetSetByCallerMagnitude(DBDGameplayTags::Object_Progress_Speed, TaskSpeed);
		SpecHandle.Data->SetSetByCallerMagnitude(DBDGameplayTags::Object_Progress_ActorCount, InteractorCount);
		OwningObjectASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}
