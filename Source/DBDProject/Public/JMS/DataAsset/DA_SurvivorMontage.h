// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_SurvivorMontage.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDA_SurvivorMontage : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* RepairGenerator;
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* RepairFailed;
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* OpenExitDoor;
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* HealSelf;
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* HealOther;
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* RescueIn;
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* RescueOut;
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* RescuedByOtherIn;
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* RescuedByOtherOut;
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* CarryStart;
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* DroppedFromKiller;
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* OpenCabinet;
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* HookIn;
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* HookOut;
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* HookDead;
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* PickedupIn;
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* HookPhase2Start;
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* RunningOnExit;
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* HookSabotage;
	UPROPERTY(EditDefaultsOnly, Category = "Survivor Montage")
	UAnimMontage* StartMontage;
};
