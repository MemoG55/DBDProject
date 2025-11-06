// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GA_Active.h"
#include "GA_Cabinet.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Cabinet : public UGA_Active
{
	GENERATED_BODY()
public:
	UGA_Cabinet();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	UPROPERTY()
	class UIC_Cabinet* IC_Cabinet;

	UPROPERTY()
	AActor* CapturedActor;
	
#pragma region CabinetMontages:
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* Montage_KillerFindSurvivor;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* Montage_KillerOpenEmpty;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* Montage_KillerOpenReload;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* Montage_SurvivorOpenHide;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* Montage_SurvivorOpenExist;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* Montage_SurvivorOpenExit;
#pragma endregion
	
};
