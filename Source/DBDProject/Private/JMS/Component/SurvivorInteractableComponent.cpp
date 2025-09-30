// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Component/SurvivorInteractableComponent.h"

#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/GAS/SurvivorAbilitySystemComponent.h"
#include "JMS/GAS/SurvivorAttributeSet.h"
#include "JMS/GAS/GE/GE_HealSurvivorFromDying.h"
#include "JMS/GAS/GE/GE_HealSurvivorFromInjured.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/Interface/Interactor.h"


USurvivorInteractableComponent::USurvivorInteractableComponent()
{
	InteractableTag = DBDGameplayTags::Interactable_Character_Survivor;
}

void USurvivorInteractableComponent::StartInteraction(AActor* Actor)
{
	Super::StartInteraction(Actor);
	SetInteractors(Actor);
	IInteractor* Interactor = Cast<IInteractor>(Actor);
	if (!Interactor)
	{
		Debug::Print(TEXT("JMS12 : SurvivorInteractableComponent : StartInteraction : Interactor is null"), 12);
		return;
	}
	ASurvivorCharacter* SurvivorCharacter = Cast<ASurvivorCharacter>(OwningActor);
	if (!SurvivorCharacter)
	{
		Debug::Print(
			TEXT("JMS13 : SurvivorInteractableComponent : StartInteraction : this is not SurvivorCharacter"), 13);
		return;
	}
	if (Interactor->GetInteractorRole() == EPlayerRole::Killer)
	{
		SurvivorCharacter->CaptureSurvivor();
	}
	else if (Interactor->GetInteractorRole() == EPlayerRole::Survivor)
	{
		GetWorld()->GetTimerManager().SetTimer(TickTimerHandle, this, &USurvivorInteractableComponent::PlayTick,
		                                       0.1f, true);
	}
}

bool USurvivorInteractableComponent::CanInteraction(AActor* Actor)
{
	IInteractor* Interactor = Cast<IInteractor>(Actor);
	if (!Interactor)
	{
		Debug::Print(TEXT("JMS11 : SurvivorInteractableComponent : CanInteraction : Interactor is null"), 11);
		return false;
	}
	if (Interactor->GetInteractorRole() == EPlayerRole::Killer)
	{
		return OwningASC->HasMatchingGameplayTag(DBDGameplayTags::Survivor_Status_CaptureEnabled);
	}
	if (Interactor->GetInteractorRole() == EPlayerRole::Survivor)
	{
		return OwningASC->HasMatchingGameplayTag(DBDGameplayTags::Survivor_Status_Injured) || OwningASC->
			HasMatchingGameplayTag(DBDGameplayTags::Survivor_Status_Dying);
	}
	return false;
}

void USurvivorInteractableComponent::TickInteraction(AActor* Actor)
{
	Super::TickInteraction(Actor);
	float TaskSpeed = GetHealSpeedAttributeValue();
	if (OwningSurvivorASC->HasMatchingGameplayTag(DBDGameplayTags::Survivor_Status_Injured))
	{
		FGameplayEffectContextHandle SpecContext = OwningSurvivorASC->MakeEffectContext();
		SpecContext.AddSourceObject(OwningActor);
		SpecContext.AddInstigator(OwningActor, OwningActor);

		FGameplayEffectSpecHandle SpecHandle = OwningSurvivorASC->MakeOutgoingSpec(
			UGE_HealSurvivorFromInjured::StaticClass(), 1, SpecContext);
		SpecHandle.Data->SetSetByCallerMagnitude(DBDGameplayTags::Survivor_SetbyCaller_HealAmount, TaskSpeed);
		OwningSurvivorASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
	else if (OwningSurvivorASC->HasMatchingGameplayTag(DBDGameplayTags::Survivor_Status_Dying))
	{
		FGameplayEffectContextHandle SpecContext = OwningSurvivorASC->MakeEffectContext();
		SpecContext.AddSourceObject(OwningActor);
		SpecContext.AddInstigator(OwningActor, OwningActor);

		FGameplayEffectSpecHandle SpecHandle = OwningSurvivorASC->MakeOutgoingSpec(
			UGE_HealSurvivorFromDying::StaticClass(), 1, SpecContext);
		SpecHandle.Data->SetSetByCallerMagnitude(DBDGameplayTags::Survivor_SetbyCaller_HealAmount, TaskSpeed);
		OwningSurvivorASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void USurvivorInteractableComponent::FinishInteraction(AActor* Actor)
{
	Super::FinishInteraction(Actor);

	UnSetInteractors(Actor);

	// ActivateGE를 StartInteraction에서 제거(공통)
	if (InteractedActors.IsEmpty())
	{
		OwningSurvivorASC->RemoveActiveGameplayEffectBySourceEffect(UGE_HealSurvivorFromInjured::StaticClass(),OwningSurvivorASC);
		OwningSurvivorASC->RemoveActiveGameplayEffectBySourceEffect(UGE_HealSurvivorFromDying::StaticClass(),OwningSurvivorASC);

	}
	OnDisconnect.Broadcast();
}

void USurvivorInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
	ASurvivorCharacter* OwningSurvivorCharacter = Cast<ASurvivorCharacter>(OwningActor);
	if (OwningSurvivorCharacter)
	{
		OwningSurvivor = OwningSurvivorCharacter;
		OwningSurvivorASC = Cast<USurvivorAbilitySystemComponent>(OwningASC);
	}
}

void USurvivorInteractableComponent::PlayTick()
{
	TickInteraction(GetOwner());
}

float USurvivorInteractableComponent::GetHealSpeedAttributeValue()
{
	if (!CheckAuthority()) return 0.f;

	if (InteractedActors.IsEmpty())
	{
		return 0.f;
	}

	float TaskSpeed = 0.f;
	float Efficiency = 1.f - 0.1f * (InteractedActors.Num() - 1);

	for (AActor* Actor : InteractedActors)
	{
		if (ADBDCharacter* Character = Cast<ADBDCharacter>(Actor))
		{
			if (UDBDAbilitySystemComponent* ASC = Cast<UDBDAbilitySystemComponent>(
				Character->GetAbilitySystemComponent()))
			{
				float CurrentActorTaskSpeed = ASC->GetNumericAttribute(USurvivorAttributeSet::GetHealSpeedAttribute());

				TaskSpeed += (CurrentActorTaskSpeed * Efficiency);
			}
		}
	}

	return TaskSpeed;
}

void USurvivorInteractableComponent::OnCompleted_Implementation()
{
	Super::OnCompleted_Implementation();
	// ActivateGE를 제거(공통)
	OwningSurvivorASC->RemoveActiveGameplayEffectBySourceEffect(UGE_HealSurvivorFromInjured::StaticClass(),OwningSurvivorASC);
	OwningSurvivorASC->RemoveActiveGameplayEffectBySourceEffect(UGE_HealSurvivorFromDying::StaticClass(),OwningSurvivorASC);
}
