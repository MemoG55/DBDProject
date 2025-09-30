// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/Interactable/DBDObject.h"
#include "MMJ/Object/Component/ICHook.h"
#include "Obj_Hook.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API AObj_Hook : public ADBDObject
{
	GENERATED_BODY()
public:
	AObj_Hook(const FObjectInitializer& ObjectInitializer);

	virtual UICHook* GetInteractableComponent() const override;

	UPROPERTY(VisibleDefaultsOnly)
	UICHook* HookInteractableComponent;

	/**
	 * 갈고리에 배치되는 엔티티
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* HookEntity;
};
