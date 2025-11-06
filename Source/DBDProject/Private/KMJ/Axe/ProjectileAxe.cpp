// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/Axe/ProjectileAxe.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "KMJ/Character/KillerHuntress.h"
#include "Shared/DBDDebugHelper.h"


// Sets default values
AProjectileAxe::AProjectileAxe()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
    AActor::SetReplicateMovement(true);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	// Owner와의 충돌을 무시하도록 설정
	//CollisionBox->SetCollisionResponseToActor(GetOwner(), ECR_Ignore);
	// Owner와의 충돌을 무시하도록 설정
	if (AActor* OwnerActor = GetOwner())
	{
		AKillerHuntress* Huntress = Cast<AKillerHuntress>(OwnerActor);
    	CollisionBox->IgnoreActorWhenMoving(Huntress, true);  // 충돌을 무시
	}

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionBox);
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 1.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
	ProjectileMeshComponent->SetupAttachment(RootComponent);

/*
	if (CollisionBox)
	{
		CollisionBox->OnComponentHit.AddDynamic(this, &AProjectileAxe::OnHit);
		CollisionBox->SetNotifyRigidBodyCollision(true); 
	}
*/
	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AProjectileAxe::OnOverlap);
		CollisionBox->SetGenerateOverlapEvents(true); // 오버랩 이벤트 활성화
	}
	else
	{
		//UE_LOG(LogTemp, Error, TEXT("ProjectileMovementComponent is NULL"));
	}

}

// Called when the game starts or when spawned
void AProjectileAxe::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileAxe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileAxe::Activate()
{
	Super::Activate();
}

void AProjectileAxe::Deactivate()
{
	Super::Deactivate();
	ProjectileMovementComponent->SetActive(false);
	CollisionBox->SetNotifyRigidBodyCollision(false);
	ProjectileMeshComponent->SetVisibility(false);
}

void AProjectileAxe::Initialize(const FVector& Location, const FVector& ShootDirection, const float Speed)
{
}

void AProjectileAxe::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                               bool bFromSweep, const FHitResult& SweepResult)
{
	//JMS: 서버에서만 실행해서 2중 공격 방지
	if (!HasAuthority())
	{
		return;
	}
	ProjectileMovementComponent->StopMovementImmediately();
	// 충돌이 발생하면 Deactivate() 호출
	//UE_LOG(LogTemp, Error, TEXT("On Overlapped Axe"));
	FString ActorClassName = OtherActor->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("충돌한 액터: %s"), *ActorClassName);
	if (OtherActor && OtherActor != Owner)
	{
		//여기에 충돌 처리
		if (ASurvivorCharacter* Survivor = Cast<ASurvivorCharacter>(OtherActor))
		{
			//생존자 데미지 처리
			Survivor->AttackSurvivor();
			//UE_LOG(LogTemp, Warning, TEXT("Throwing Axe Hit Survivor!"));
		}
	}
	//TODO::부서지는 이펙트 추가해야함
	// Spawn impact effect
	if (ImpactEffect)
	{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, SweepResult.ImpactPoint, SweepResult.ImpactNormal.Rotation());
	}
	//투척도끼 비활성화
	//UE_LOG(LogTemp, Display, TEXT("Axe Deactivate"));
	//Debug::Print(TEXT("Throwing Axe Deactivate"), 325);
	Deactivate();
}

void AProjectileAxe::ShootInDirection(const FVector& ShootDirection, const float Speed)
{
	ProjectileMovementComponent->InitialSpeed = Speed;
	ProjectileMovementComponent->MaxSpeed = Speed;
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}
