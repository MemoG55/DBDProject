// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/Component/ICObject.h"
#include "IC_Pallet.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UIC_Pallet : public UICObject
{
	GENERATED_BODY()
public:
	UIC_Pallet();

	virtual void StartInteraction(AActor* Actor) override;
	virtual void FinishInteraction(AActor* Actor) override;
	
	virtual void CompleteInteraction(AActor* Actor) override;
	virtual void DestroyInteraction(AActor* Actor) override;

protected:
	virtual void SetInteractors(AActor* Actor) override;
	virtual void UnSetInteractors(AActor* Actor) override;
};
