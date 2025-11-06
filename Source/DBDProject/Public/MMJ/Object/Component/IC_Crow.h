// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/Component/ICObject.h"
#include "IC_Crow.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UIC_Crow : public UICObject
{
	GENERATED_BODY()
public:
	UIC_Crow();

protected:
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	virtual void StartInteraction(AActor* Actor) override;
	virtual void FinishInteraction(AActor* Actor) override;

private:
	UPROPERTY()
	FTimerHandle FindInteractorTimer;

	float FindInteractorInterval = 0.1f;
	float MaxFindInteractorTime = 2.f;

	UFUNCTION()
	void FindInteractor();
	
};
