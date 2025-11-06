// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KMJ/GAS/KillerGameplayAbility.h"
#include "GA_Locker_Killer.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UGA_Locker_Killer : public UKillerGameplayAbility
{
	GENERATED_BODY()

protected:
	//탐색 시작 몽타주
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="GA_Locker", meta=(AllowPrivateAccess=true))
	UAnimMontage* FPVSearchMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="GA_Locker", meta=(AllowPrivateAccess=true))
	UAnimMontage* TPVSearchMontage;

	//Result1. Nothing
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="GA_Locker", meta=(AllowPrivateAccess=true))
	UAnimMontage* FPVNoneMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="GA_Locker", meta=(AllowPrivateAccess=true))
	UAnimMontage* TPVNoneMontage;

	//Result2. Capture Hiding Survivor
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="GA_Locker", meta=(AllowPrivateAccess=true))
	UAnimMontage* FPVCaptureMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="GA_Locker", meta=(AllowPrivateAccess=true))
	UAnimMontage* TPVCaptureMontage;
	
};
