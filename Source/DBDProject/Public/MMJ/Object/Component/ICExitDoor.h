// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ICObject.h"
#include "ICExitDoor.generated.h"

class AObj_Exit;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UICExitDoor : public UICObject
{
	GENERATED_BODY()
public:
	UICExitDoor();
protected:
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void StartInteraction(AActor* Actor) override;
	virtual void TickInteraction(AActor* Actor) override;

	virtual void UnSetInteractors(AActor* Actor) override;
	
	virtual void OnCompleted_Implementation() override;
	

public:
	virtual bool CanInteraction(AActor* Actor) override;

	
};
