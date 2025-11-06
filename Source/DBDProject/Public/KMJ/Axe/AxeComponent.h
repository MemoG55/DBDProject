// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AxeComponent.generated.h"

class APoolableActor;
class AProjectileAxe;
class AKillerHuntress;
class UHuntressAttributeSet;
class AGenericPool;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DBDPROJECT_API UAxeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAxeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	USkeletalMeshComponent* SkeletalMeshComponent;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Axe")
	TSubclassOf<AKillerHuntress> BPHuntress;*/
	AKillerHuntress* Huntress = nullptr;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Axe") // For debug
	void FireWeapon();
	UFUNCTION(Server, Reliable)
	void Server_FireWeapon(const FVector& MuzzleLocation, const FVector& ShootDirection);

	UFUNCTION()
	void InitProjectilePool(float NewAxeNum);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Axe")
	TSubclassOf<AProjectileAxe> Projectile;
	UPROPERTY()
	AGenericPool* ProjectilePool;

	UPROPERTY()
	bool bIsChargingThrow;
	
	UFUNCTION(BlueprintCallable, Category = "Axe")
	void DrawPredictedPath();

	UFUNCTION(BlueprintCallable, Category = "Axe")
	void ClearPredictedPath();

	UFUNCTION(BlueprintCallable)
	void StartChargingThrow();

	UFUNCTION(BlueprintCallable)
	void StopChargingThrow();
};
