// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolableActor.h"
#include "GameFramework/Actor.h"
#include "ProjectileAxe.generated.h"

class UProjectileMovementComponent;

UCLASS()
class DBDPROJECT_API AProjectileAxe : public APoolableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileAxe();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Activate() override;
	UFUNCTION(BlueprintCallable)
	virtual void Deactivate() override;
	void Initialize(const FVector& Location, const FVector& ShootDirection, const float Speed);
/*
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
						FVector NormalImpulse, const FHitResult& Hit);
*/
						
	UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                   bool bFromSweep, const FHitResult& SweepResult);
    
	UFUNCTION()
	void ShootInDirection(const FVector& ShootDirection, const float Speed);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovementComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Killer", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMeshComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Killer", meta=(AllowPrivateAccess = "true"))
	UParticleSystem* ImpactEffect;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public: 
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionBox;
};
