// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/Interactable/DBDObject.h"
#include "MMJ/Object/Interface/EntitySpawnable.h"
#include "Obj_Pallet.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API AObj_Pallet : public ADBDObject, public IEntitySpawnable
{
	GENERATED_BODY()
public:
	AObj_Pallet(const FObjectInitializer& ObjectInitializer);

	virtual void SpawnEntity() override;

protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Pallet_Broken;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Pallet_Broken_Disappear;

protected:
	virtual void OnRep_IsDestroyed() override;
};
