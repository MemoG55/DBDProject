// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/Axe/AxeComponent.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "KMJ/AbilitySystem/HuntressAttributeSet.h"
#include "KMJ/Axe/GenericPool.h"
#include "KMJ/Axe/ProjectileAxe.h"
#include "KMJ/Character/KillerHuntress.h"
#include "Net/UnrealNetwork.h"
#include "ProfilingDebugging/StallDetector.h"


// Sets default values for this component's properties
UAxeComponent::UAxeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UAxeComponent::BeginPlay()
{
	Super::BeginPlay();

	// 월드에서 AKillerHuntress 객체 하나를 찾기
	Huntress = Cast<AKillerHuntress>(GetOwner());
	if (Huntress)
	{
		// Huntress가 유효하다면 SkeletalMeshComponent 설정
		SkeletalMeshComponent = Huntress->GetMesh();
	}
	
}

// Called every frame
void UAxeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsChargingThrow)
	{
		DrawPredictedPath();
	}
}

void UAxeComponent::FireWeapon()
{
	// 뷰포트 접근은 클라이언트에서만
	if (GetNetMode() == NM_DedicatedServer)
	{
		return;
	}

	if (!GEngine || !GEngine->GameViewport)
	{
		return;
	}
	
	FTransform SocketTransform = SkeletalMeshComponent->GetSocketTransform("AxeSpawn", RTS_World);
	FVector MuzzleLocation = SocketTransform.GetLocation();

	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	FVector2D ScreenCenter(ViewportSize.X / 2, ViewportSize.Y / 2);

	FVector WorldLocation, WorldDirection;
	if (UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(GetWorld(), 0),
		ScreenCenter,
		WorldLocation,
		WorldDirection))
	{
		FVector Start = WorldLocation;
		FVector End = Start + (WorldDirection * 10000);
		FHitResult HitResult;

		FVector HitLocation = End;
		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility))
		{
			HitLocation = HitResult.Location;
		}

		FVector ShootDirection = (HitLocation - MuzzleLocation).GetSafeNormal();

		// 서버에 방향 전달
		Server_FireWeapon(MuzzleLocation, ShootDirection);
	}
}

void UAxeComponent::Server_FireWeapon_Implementation(const FVector& MuzzleLocation, const FVector& ShootDirection)
{
	if (!Projectile) return;
	bIsChargingThrow = false;
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = Cast<APawn>(GetOwner());

	AProjectileAxe* SpawnedProjectileActor = ProjectilePool->GetObject<AProjectileAxe>(Projectile);
	if (SpawnedProjectileActor && SpawnedProjectileActor->IsA(Projectile))
	{
		SpawnedProjectileActor->SetActorLocation(MuzzleLocation);
		SpawnedProjectileActor->SetActorRotation(ShootDirection.Rotation());

		if (SpawnedProjectileActor->ProjectileMovementComponent)
		{
			SpawnedProjectileActor->ProjectileMovementComponent->Activate(true);
			SpawnedProjectileActor->ProjectileMovementComponent->SetUpdatedComponent(SpawnedProjectileActor->CollisionBox);
			SpawnedProjectileActor->ProjectileMovementComponent->ProjectileGravityScale = 1.0f;
			const float Speed = Huntress->HuntressAttributeSet->AxeMaxSpeed.GetCurrentValue();
			SpawnedProjectileActor->ShootInDirection(ShootDirection, Speed);
		}
		// Collision 및 기타 활성화
		SpawnedProjectileActor->Activate();
	}
}

void UAxeComponent::InitProjectilePool(float NewAxeNum)
{
	if (!ProjectilePool || ProjectilePool->ObjectPool.Num() == 0)
	{
		// Object Pool 초기화
		ProjectilePool = GetWorld()->SpawnActor<AGenericPool>();
		int AxeNum = NewAxeNum;
		ProjectilePool->InitPool<AProjectileAxe>(Projectile, AxeNum);
	}
}

void UAxeComponent::DrawPredictedPath()
{
	if (!Huntress || !SkeletalMeshComponent) return;

	FTransform SocketTransform = SkeletalMeshComponent->GetSocketTransform("AxeSpawn", RTS_World);
	FVector StartLocation = SocketTransform.GetLocation();

	FVector2D ViewportSize;
	if (!GEngine || !GEngine->GameViewport) return;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	FVector2D ScreenCenter(ViewportSize.X / 2, ViewportSize.Y / 2);

	FVector WorldLocation, WorldDirection;
	if (!UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(GetWorld(), 0),
		ScreenCenter,
		WorldLocation,
		WorldDirection))
	{
		return;
	}

	const float Speed = Huntress->HuntressAttributeSet->AxeMaxSpeed.GetCurrentValue();
	FVector LaunchVelocity = WorldDirection * Speed;

	FPredictProjectilePathParams Params;
	FPredictProjectilePathResult Result;

	Params.StartLocation = StartLocation;
	Params.LaunchVelocity = LaunchVelocity;
	Params.ProjectileRadius = 5.f;
	Params.MaxSimTime = 3.f;
	Params.bTraceWithCollision = true;
	Params.OverrideGravityZ = -980.f;
	Params.SimFrequency = 15.f;
	Params.DrawDebugType = EDrawDebugTrace::None;
	Params.ActorsToIgnore.Add(Huntress);

	UGameplayStatics::PredictProjectilePath(GetWorld(), Params, Result);

	// 흰색으로 라인 표시 (조준 중에만)
	for (int32 i = 0; i < Result.PathData.Num() - 1; i++)
	{
		DrawDebugLine(GetWorld(),
			Result.PathData[i].Location,
			Result.PathData[i + 1].Location,
			FColor::White,
			false,
			0.0f,
			0,
			2.f);
	}

	if (Result.HitResult.bBlockingHit)
	{
		DrawDebugSphere(GetWorld(), Result.HitResult.Location, 8.f, 12, FColor::White, false, 0.05f);
	}
}


// 궤적 지우기
void UAxeComponent::ClearPredictedPath()
{
	FlushPersistentDebugLines(GetWorld());
}

void UAxeComponent::StartChargingThrow()
{
	bIsChargingThrow = true;
}

void UAxeComponent::StopChargingThrow()
{
	bIsChargingThrow = false;
	ClearPredictedPath();
}