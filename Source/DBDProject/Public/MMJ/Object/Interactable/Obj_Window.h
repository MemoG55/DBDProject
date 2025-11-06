// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/Interactable/DBDObject.h"
#include "MMJ/Object/Interface/EntitySpawnable.h"
#include "Obj_Window.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API AObj_Window : public ADBDObject, public IEntitySpawnable
{
	GENERATED_BODY()
public:
	AObj_Window(const FObjectInitializer& ObjectInitializer);

	virtual void SpawnEntity() override;

	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* GetStaticMeshComponent() const { return ObjectStaticMesh;	}
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,  Category = "Object")
	UStaticMeshComponent* ObjectStaticMesh;

	
};
