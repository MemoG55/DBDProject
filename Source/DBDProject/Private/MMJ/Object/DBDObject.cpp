// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/DBDObject.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "MMJ/Object/GAS/ObjAbilitySystemComponent.h"
#include "MMJ/Object/GAS/ObjAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "Shared/DBDGameplayTags.h"

// Sets default values
ADBDObject::ADBDObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bAlwaysRelevant = true;
	bReplicates = true;

	ObjectMesh = CreateDefaultSubobject<USkeletalMeshComponent>("ObjectMesh");
	ObjectMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	ObjectMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	SetRootComponent(ObjectMesh);

	ObjectCollision = CreateDefaultSubobject<UBoxComponent>("ObjectCollision");
	ObjectCollision->SetupAttachment(GetRootComponent());
	ObjectCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	ObjectCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	ObjectCollision->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);

	ObjAbilitySystemComponent = CreateDefaultSubobject<UObjAbilitySystemComponent>("ObjAbilitySystemComponent");
	ObjAttributeSet = CreateDefaultSubobject<UObjAttributeSet>("ObjAttributeSet");
	
}

UAbilitySystemComponent* ADBDObject::GetAbilitySystemComponent() const
{
	return ObjAbilitySystemComponent;
}

void ADBDObject::Init()
{
}

// Called when the game starts or when spawned
void ADBDObject::BeginPlay()
{
	Super::BeginPlay();
	if (ObjAbilitySystemComponent && HasAuthority())
	{
		ObjAbilitySystemComponent->InitAbilityActorInfo(this, this);
		ObjAbilitySystemComponent->ServerSideInit();


		// TODO:: 액티베이션 어빌리티 왜 안되는지 확인하기
		if (TestAbility && false)
		{
			FGameplayAbilitySpec Spec = FGameplayAbilitySpec(TestAbility, 1, 1, nullptr);
			ObjAbilitySystemComponent->GiveAbility(Spec);
			ObjAbilitySystemComponent->TryActivateAbility(Spec.Handle);	
		}
	}
}

void ADBDObject::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ADBDObject, bIsActive, COND_None, REPNOTIFY_Always);
}

// Called every frame
void ADBDObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADBDObject::Interaction_Implementation(AActor* Actor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, DBDGameplayTags::Object_Status_IsActive, FGameplayEventData());
	UE_LOG(LogTemp, Warning, TEXT("Interaction"));
	
	/*
	if (HasAuthority())
	{
		ObjAbilitySystemComponent->AddLooseGameplayTag(DBDGameplayTags::Object_Status_IsActive);
	}
	else
	{
		Server_AddTagToObject(DBDGameplayTags::Object_Status_IsActive);
	}
	*/
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

void ADBDObject::OnRep_IsActive()
{
}

void ADBDObject::Server_AddTagToObject_Implementation(FGameplayTag Tag)
{
	if (ObjAbilitySystemComponent)
	{
		ObjAbilitySystemComponent->AddLooseGameplayTag(Tag);
	}
}


