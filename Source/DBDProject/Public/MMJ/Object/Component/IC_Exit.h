// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ICObject.h"
#include "IC_Exit.generated.h"

class AObj_ExitDoor;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UIC_Exit : public UICObject
{
	GENERATED_BODY()
protected:
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	AObj_ExitDoor* ExitDoor;

	UFUNCTION()
	void SetActivate();
};
