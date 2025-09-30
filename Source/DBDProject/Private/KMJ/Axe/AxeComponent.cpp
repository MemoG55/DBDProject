// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/Axe/AxeComponent.h"

#include "Kismet/GameplayStatics.h"
#include "KMJ/AbilitySystem/HuntressAttributeSet.h"
#include "KMJ/Axe/GenericPool.h"
#include "KMJ/Axe/ProjectileAxe.h"
#include "KMJ/Character/KillerHuntress.h"


// Sets default values for this component's properties
UAxeComponent::UAxeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAxeComponent::BeginPlay()
{
	Super::BeginPlay();

	// 월드에서 AKillerHuntress 객체 하나를 찾기
	Huntress = Cast<AKillerHuntress>(UGameplayStatics::GetActorOfClass(GetWorld(), AKillerHuntress::StaticClass()));
	if (Huntress)
	{
		// Huntress가 유효하다면 SkeletalMeshComponent 설정
		SkeletalMeshComponent = Huntress->GetMesh();
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("No AKillerHuntress found in the world"));
	}
	
	// Object Pool 초기화
	ProjectilePool = GetWorld()->SpawnActor<AGenericPool>();
	if (Huntress)
	{
		const FGameplayAttributeData& AxeAttr = Huntress->HuntressAttributeSet->GetAxeNumber();
		int AxeNum = AxeAttr.GetCurrentValue();
		ProjectilePool->InitPool<AProjectileAxe>(AxeNum);
	}
	
}


// Called every frame
void UAxeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
		//UE_LOG(LogTemp, Warning, TEXT("뷰포트 없음"));
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

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = Cast<APawn>(GetOwner());

	AProjectileAxe* SpawnedProjectile = GetWorld()->SpawnActor<AProjectileAxe>(
		Projectile,
		MuzzleLocation,
		ShootDirection.Rotation(),
		SpawnParams
	);

	if (SpawnedProjectile)
	{
		const FGameplayAttributeData& AxeAttr = Huntress->HuntressAttributeSet->GetAxeMaxSpeed();
		float Speed = AxeAttr.GetCurrentValue();
		SpawnedProjectile->Activate();
		SpawnedProjectile->ShootInDirection(ShootDirection, Speed);
	}
}

