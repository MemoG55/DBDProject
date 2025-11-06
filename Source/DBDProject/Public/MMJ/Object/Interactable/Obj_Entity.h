// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/Interactable/DBDObject.h"
#include "Obj_Entity.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API AObj_Entity : public ADBDObject
{
	GENERATED_BODY()
public:
	AObj_Entity(const FObjectInitializer& ObjectInitializer);

	UPROPERTY()
	ADBDObject* OwnerObject;

	UPROPERTY()
	UICObject* OwnerObjIC;

	UFUNCTION()
	UStaticMeshComponent* GetStaticMeshComponent() const;

#pragma region Dissolve:
	// 0 ~ 3
	float MaxDissolveAmount = 3.f;

	UPROPERTY(Replicatedusing = OnRep_DissolveAmount)
	float DissolveAmount;

	UFUNCTION()
	void SetDissolve(float Percent);

	UFUNCTION()
	void OnRep_DissolveAmount();

#pragma endregion


#pragma region Activate:
	// Dissolve 트리거로 사용할 bool변수
	UPROPERTY(ReplicatedUsing = OnRep_IsActive)
	bool bIsActive = false;

	UFUNCTION()
	void OnRep_IsActive();

	UFUNCTION()
	void SetActive();

	UFUNCTION()
	void SetInActive();
	
#pragma endregion
	
protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* ObjectStaticMesh;
};
