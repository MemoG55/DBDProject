// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/Component/ICObject.h"
#include "Shared/Interface/Capturable.h"
#include "IC_Cabinet.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UIC_Cabinet : public UICObject, public ICapturable
{
	GENERATED_BODY()
public:
	UIC_Cabinet();

	UFUNCTION(BlueprintCallable)
	virtual void Capture(AActor* Actor) override;

	virtual void StartInteraction(AActor* Actor) override;
	virtual void FinishInteraction(AActor* Actor) override;

	
protected:
	virtual void SetInteractors(AActor* Actor) override;
	virtual void UnSetInteractors(AActor* Actor) override;

public:
	virtual bool CanInteraction(AActor* Actor) override;
	
};
