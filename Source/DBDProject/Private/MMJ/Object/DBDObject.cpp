// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/DBDObject.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MMJ/Object/ObjFunctionLibrary.h"
#include "MMJ/Object/DataAsset/ObjDataAsset.h"
#include "MMJ/Object/GAS/ObjAbilitySystemComponent.h"
#include "MMJ/Object/GAS/ObjAttributeSet.h"
#include "MMJ/Object/GAS/GE/ObjGE_Active.h"
#include "Net/UnrealNetwork.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/GameFramework/DBDPlayerState.h"

// Sets default values
ADBDObject::ADBDObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bAlwaysRelevant = true;
	bReplicates = true;
	
	ObjectMesh = CreateDefaultSubobject<USkeletalMeshComponent>("ObjectMesh");
	ObjectMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	ObjectMesh->SetCollisionObjectType(ECC_WorldStatic);
	SetRootComponent(ObjectMesh);

	ObjectCollision = CreateDefaultSubobject<UBoxComponent>("ObjectCollision");
	ObjectCollision->SetupAttachment(GetRootComponent());
	ObjectCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	ObjectCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	ObjectCollision->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);

	ObjAbilitySystemComponent = CreateDefaultSubobject<UObjAbilitySystemComponent>("ObjAbilitySystemComponent");
	ObjAttributeSet = CreateDefaultSubobject<UObjAttributeSet>("ObjAttributeSet");

	OnInteractWithActor.AddDynamic(this, &ThisClass::SetInteractors);
	OnDisconnectWithActor.AddDynamic(this, &ThisClass::UnSetInteractors);
	OnComplete.AddDynamic(this, &ThisClass::OnInteractionEnded);
}

UAbilitySystemComponent* ADBDObject::GetAbilitySystemComponent() const
{
	return ObjAbilitySystemComponent;
}

void ADBDObject::Init()
{
}

void ADBDObject::SearchNearbyActors()
{
	TArray<AActor*> AllActors;
	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::SphereTraceMulti(GetWorld(), GetActorLocation(), GetActorLocation(), 200.f,
		TraceTypeQuery1, false, AllActors, EDrawDebugTrace::Type::ForDuration, HitResults, true);

	TSet<AActor*> UniqueActors;
	for (const FHitResult& HitResult : HitResults)
	{
		if (IAbilitySystemInterface* ASC = Cast<IAbilitySystemInterface>(HitResult.GetActor()))
		{
			UniqueActors.Add(HitResult.GetActor());
		}
	}

	for (AActor* Actor : UniqueActors)
	{
		SetInteractors(Actor);
	}
}

// Called when the game starts or when spawned
void ADBDObject::BeginPlay()
{
	Super::BeginPlay();
	if (ObjAbilitySystemComponent && HasAuthority())
	{
		ObjAbilitySystemComponent->InitAbilityActorInfo(this, this);
		ObjAbilitySystemComponent->SetIsReplicated(true);
		ObjAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
		ObjAbilitySystemComponent->ServerSideInit();

		ObjAbilitySystemComponent->RegisterGameplayTagEvent(DBDGameplayTags::Object_Status_IsDestroy, EGameplayTagEventType::NewOrRemoved)
		.AddUObject(this, &ThisClass::OnDestroyed);
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


void ADBDObject::Interaction_Implementation(AActor* Actor)
{
	if (HasAuthority())
	{
		StartInteraction(Actor);
	}
}

void ADBDObject::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(OtherActor))
	{
		InteractedActors.Add(OtherActor);
	}
}

void ADBDObject::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnDisconnectWithActor.Broadcast(OtherActor);
}

void ADBDObject::StartInteraction(AActor* Actor)
{
	bIsActive = true;

	if (HasAuthority())
	{
		bool Activation = false;
		// Actor가 살인마인지, 생존자인지 판별하는 로직
		if (UObjFunctionLibrary::IsKiller(Actor))
		{
			Activation = true;
			ObjAbilitySystemComponent->AddLooseGameplayTag(DBDGameplayTags::Object_Status_IsDestroy);
		}
		else if (UObjFunctionLibrary::IsSurvivor(Actor))
		{
			Activation = true;
			ObjAbilitySystemComponent->AddLooseGameplayTag(DBDGameplayTags::Object_Status_IsActive);
		}
		if (Activation)
		{
			// 해당 액터가 상호작용을 시작했을 때 델리게이트 호출
			OnInteractWithActor.Broadcast(Actor);
			OnInteract.Broadcast();
		}
	}
}

void ADBDObject::TickInteraction(AActor* Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("MMJ : %s Task Tick With Actor %s "), *GetName(), *Actor->GetName());
}

void ADBDObject::EndInteraction(AActor* Actor)
{
	//bIsActive = false;
	//UE_LOG(LogTemp, Warning, TEXT("MMJ : %s Task End With Actor %s "), *GetName(), *Actor->GetName());
	OnDisconnectWithActor.Broadcast(Actor);
}

void ADBDObject::CompleteInteraction(AActor* Actor)
{
	//UE_LOG(LogTemp, Warning, TEXT("MMJ : %s Task Complete With Actor %s "), *GetName(), *Actor->GetName());
	bIsActive = false;
	bIsComplete = true;
	OnCompleteWithActor.Broadcast(Actor);
}

void ADBDObject::CancelInteraction(AActor* Actor)
{
	//UE_LOG(LogTemp, Warning, TEXT("MMJ : %s Task Cancel With Actor"), *GetName());
	OnDisconnectWithActor.Broadcast(Actor);
}

bool ADBDObject::CanInteraction(AActor* Actor)
{
	if (ObjAbilitySystemComponent)
	{
		// 상호작용이 가능한 경우는 총 2가지(아래는 발전기예시)
		// 1. CurrentTask != MaxTask ( IsComplete 태그가 붙지 않은 경우)
		// 2. 현재 상호작용중인 인원 수가 총 인원보다 적을 때

		// 살인마는 그냥 인터랙트 가능함(테스트용도)
		if (UObjFunctionLibrary::IsKiller(Actor))
		{
			return true;
		}

		if ( (!ObjAbilitySystemComponent->IsMaxTask() || MaxInteractorCount == InteractedActors.Num())
			&& !UDBDBlueprintFunctionLibrary::NativeActorHasTag(this, DBDGameplayTags::Object_Status_IsComplete))
		{
			return true;
		}
	}
	return false;
}

TArray<AActor*> ADBDObject::GetInteractors()
{
	return InteractedActors;
}

void ADBDObject::SetInteractors(AActor* Actor)
{
	if (!InteractedActors.Contains(Actor))
	{
		InteractedActors.Add(Actor);
	}
	// TODO :: 매핑컨텍스트(상호작용 + 스킬체크 키) 전달
	
	// TODO :: UI 활성화
}

void ADBDObject::UnSetInteractors(AActor* Actor)
{
	InteractedActors.RemoveAll([Actor](const AActor* InteractedActor){ return InteractedActor == Actor; });
	// TODO :: 매핑컨텍스트(상호작용 + 스킬체크 키) 제거

	// TODO :: UI 비활성화
}

float ADBDObject::GetInteractionProgress()
{
	bool bFound = false;
	float CurrentTask = ObjAbilitySystemComponent->GetGameplayAttributeValue(ObjAttributeSet->GetCurrentTaskAttribute(), bFound);
	float MaxTask = ObjAbilitySystemComponent->GetGameplayAttributeValue(ObjAttributeSet->GetMaxTaskAttribute(), bFound);
	if (bFound && CurrentTask >= MaxTask)
	{
		return CurrentTask / MaxTask;
	}
	return 0.f;
}

float ADBDObject::GetInteractionDuration(AActor* Actor)
{
	return 0.f;
}

void ADBDObject::OnInteractionStarted()
{
	UE_LOG(LogTemp, Warning, TEXT("MMJ : %s Task Started"), *GetName());
}

void ADBDObject::OnInteractionEnded()
{
	UE_LOG(LogTemp, Warning, TEXT("MMJ : %s Task End"), *GetName());
}


void ADBDObject::OnDestroyed(FGameplayTag Tag, int32 count)
{
	if (ObjAbilitySystemComponent && HasAuthority())
	{
		if (ObjAbilitySystemComponent->GetObjDataAsset()->DestroyEffect)
		{
			FGameplayEffectContextHandle SpecHandle = ObjAbilitySystemComponent->MakeEffectContext();
			FGameplayEffectSpecHandle Spec = ObjAbilitySystemComponent->MakeOutgoingSpec(ObjAbilitySystemComponent->GetObjDataAsset()->DestroyEffect, 1, SpecHandle);
			ObjAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
		}
	}
}

void ADBDObject::SetIsActive(bool Activation)
{
	bIsActive = Activation;
}

bool ADBDObject::GetIsActive()
{
	return bIsActive;
}

void ADBDObject::SetCanActive(bool Activation)
{
	bCanActive = Activation;
}

bool ADBDObject::GetCanActive()
{
	return bCanActive;
}

void ADBDObject::SetIsComplete(bool bComplete)
{
	bIsComplete = bComplete;
}

bool ADBDObject::GetIsComplete()
{
	return bIsComplete;
}

