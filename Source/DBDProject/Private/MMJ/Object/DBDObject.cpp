// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/DBDObject.h"

#include "MMJ/Object/GAS/ObjAbilitySystemComponent.h"
#include "MMJ/Object/GAS/ObjAttributeSet.h"

// Sets default values
ADBDObject::ADBDObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ObjectMesh = CreateDefaultSubobject<USkeletalMeshComponent>("ObjectMesh");
	SetRootComponent(ObjectMesh);

	ObjectCollision = CreateDefaultSubobject<UBoxComponent>("ObjectCollision");
	ObjectCollision->SetupAttachment(GetRootComponent());
	ObjectCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	ObjectCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	ObjectCollision->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);

	ObjAbilitySystemComponent = CreateDefaultSubobject<UObjAbilitySystemComponent>("ObjAbilitySystemComponent");
	ObjAttributeSet = CreateDefaultSubobject<UObjAttributeSet>("ObjAttributeSet");
	
}

void ADBDObject::Init()
{
}

// Called when the game starts or when spawned
void ADBDObject::BeginPlay()
{
	Super::BeginPlay();
	if (ObjAbilitySystemComponent)
	{
		ObjAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void ADBDObject::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

// Called every frame
void ADBDObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADBDObject::Interaction(AActor* Actor) const
{
	// 자식에서 구현
}

void ADBDObject::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ADBDObject::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ADBDObject::StartInteraction(AActor* Actor)
{
}

void ADBDObject::TickInteraction(AActor* Actor)
{
}

void ADBDObject::EndInteraction(AActor* Actor)
{
}

void ADBDObject::CancelInteraction(AActor* Actor)
{
}

bool ADBDObject::CanInteraction(AActor* Actor)
{
	return false;
}

TArray<AActor*> ADBDObject::GetInteractors()
{
	return TArray<AActor*>();
}

float ADBDObject::GetInteractionProgress()
{
	return 0.f;
}

float ADBDObject::GetInteractionDuration(AActor* Actor)
{
	return 0.f;
}

void ADBDObject::OnInteractionStarted()
{
}

void ADBDObject::OnInteractionEnded()
{
}


