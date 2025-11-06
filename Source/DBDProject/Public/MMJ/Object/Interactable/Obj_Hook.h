// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/GAS/GA/Object/Active/GA_EntityHook.h"
#include "MMJ/Object/Interactable/DBDObject.h"
#include "MMJ/Object/Interface/EntitySpawnable.h"
#include "Obj_Hook.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API AObj_Hook : public ADBDObject, public IEntitySpawnable
{
	GENERATED_BODY()
public:
	AObj_Hook(const FObjectInitializer& ObjectInitializer);

	virtual void SpawnEntity() override;

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION()
	void SetHookPhase(EHookPhase Phase);

	UFUNCTION(BlueprintPure)
	EHookPhase GetHookPhase() const;
private:
	UPROPERTY(Replicated)
	EHookPhase HookPhase;
};
