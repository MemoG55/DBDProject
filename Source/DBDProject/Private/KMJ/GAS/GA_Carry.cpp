// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/GAS/GA_Carry.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "KMJ/Character/KillerCharacter.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Component/InteractableComponent.h"
#include "Shared/Component/InteractorComponent.h"


UGA_Carry::UGA_Carry()
{
}

void UGA_Carry::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//UE_LOG(LogTemp, Warning, TEXT("UGA_Carry::ActivateAbility"));

	//Killer 존재하는지 확인
	Killer = Cast<AKillerCharacter>(ActorInfo->OwnerActor);
	if (Killer == nullptr)
	{
		//UE_LOG(LogTemp,Error, TEXT("KillerActor: Nullptr"));
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}
	//UE_LOG(LogTemp,Warning, TEXT("KillerActor: %s"), *Killer->GetName());
	//Killer의 InteractWithCurrentInteractable 실행
	Killer->GetInteractorComponent()->InteractWithCurrentInteractable();
	if (Killer->IsCarriedSurvivorExist())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}
	//Interact 가능한 Survivor 있는지 확인
	InteractableSurvivorCharacter = GetInteractableSurvivorCharacter();
	if (InteractableSurvivorCharacter == nullptr)
	{
		//UE_LOG(LogTemp,Error, TEXT("InteractableSurvivorCharacter: Nullptr"));	
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}
	//UE_LOG(LogTemp,Warning, TEXT("InteractableSurvivorCharacter: %s"), *InteractableSurvivorCharacter->GetName());
	//킬러가 현재 들고 있는 생존자에 값 할당
	Killer->SetCarriedSurvivorCharacter(InteractableSurvivorCharacter);
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

UAnimMontage* UGA_Carry::GetAnimMontage(int num)
{
	switch (num)
	{
		case 0:
		return FPVStartMontage;
		case 1:
		return TPVStartMontage;
		default:
		return nullptr;
	}
}