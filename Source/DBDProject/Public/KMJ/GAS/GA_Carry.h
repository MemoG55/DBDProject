// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "KMJ/Character/KillerCharacter.h"
#include "KMJ/GAS/KillerGameplayAbility.h"
#include "Shared/Component/InteractableComponent.h"
#include "Shared/Component/InteractorComponent.h"
#include "GA_Carry.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Carry : public UKillerGameplayAbility
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* FPVStartMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* TPVStartMontage;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	AKillerCharacter* Killer = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	ASurvivorCharacter* InteractableSurvivorCharacter = nullptr;

public:
	UGA_Carry();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	AKillerCharacter* GetKillerCharacter(){return Killer;};
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void SetKillerCharacter(AActor* InputKillerCharacter){ Killer = Cast<AKillerCharacter>(InputKillerCharacter);};

	UFUNCTION(BlueprintPure, Category = "Ability")
	ASurvivorCharacter* GetInteractableSurvivorCharacter()
	{
		InteractableSurvivorCharacter = Cast<ASurvivorCharacter>(Killer->GetInteractorComponent()->GetCurrentInteractableActor());
		return InteractableSurvivorCharacter;
	};

	UFUNCTION(BlueprintCallable, Category = "Ability")
	UAnimMontage* GetAnimMontage(int num);
};
