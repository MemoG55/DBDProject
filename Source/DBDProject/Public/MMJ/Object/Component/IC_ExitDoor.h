// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ICObject.h"
#include "IC_ExitDoor.generated.h"

class AObj_Exit;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UIC_ExitDoor : public UICObject
{
	GENERATED_BODY()
public:
	UIC_ExitDoor();
protected:
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
public:
	virtual bool CanInteraction(AActor* Actor) override;

	
};
