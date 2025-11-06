// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Interactable/DBDObject.h"

#include "Components/WidgetComponent.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "MMJ/Object/Component/ICObject.h"
#include "MMJ/Object/GAS/ObjAbilitySystemComponent.h"
#include "MMJ/Object/GAS/ObjAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "Shared/Component/InteractableComponent.h"

FName ADBDObject::InteractableComponentName = TEXT("InteractableComponent");

// Sets default values
ADBDObject::ADBDObject(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bAlwaysRelevant = true;
	bReplicates = true;
	//bNetLoadOnClient = false;
	
	ObjectMesh = CreateDefaultSubobject<USkeletalMeshComponent>("ObjectMesh");
	ObjectMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	ObjectMesh->SetCollisionObjectType(ECC_WorldStatic);
	SetRootComponent(ObjectMesh);


	ObjAbilitySystemComponent = CreateDefaultSubobject<UObjAbilitySystemComponent>("ObjAbilitySystemComponent");
	ObjAttributeSet = CreateDefaultSubobject<UObjAttributeSet>("ObjAttributeSet");

	InteractableComponent = CreateDefaultSubobject<UICObject>(InteractableComponentName);
	InteractableComponent->SetupAttachment(GetRootComponent());
	InteractableComponent->SetCollisionProfileName(FName("InteractionOnly"));
	//InteractableComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	//InteractableComponent->SetCollisionObjectType(ECC_WorldDynamic);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Widget");
	WidgetComponent->SetupAttachment(GetRootComponent());
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen); // 스크린 공간
	WidgetComponent->SetDrawSize(FVector2D(10.0f, 3.0f));

	AuraMesh = CreateDefaultSubobject<UStaticMeshComponent>("AuraMesh");
	AuraMesh->SetupAttachment(GetRootComponent());
	
}

UAbilitySystemComponent* ADBDObject::GetAbilitySystemComponent() const
{
	return ObjAbilitySystemComponent;
}

void ADBDObject::Init()
{
	AuraMesh->SetVisibility(false);
}

void ADBDObject::OnRep_AuraStencilMap()
{
	const FStencilMap* FoundStencilMap = nullptr;
	
	for (const FStencilMap& StencilMap : StencilMaps)
	{
		if (StencilMap.PlayerState)
		{
			if (StencilMap.PlayerState->GetPlayerController())
			{
				if (StencilMap.PlayerState->GetPlayerController()->IsLocalController())
				{
					FoundStencilMap = &StencilMap;
				}
			}
		}
	}

	if (FoundStencilMap)
	{
		EnableAura();
		if (FoundStencilMap->bUseBackground)
		{
			EnableBackground();
		}
		else
		{
			DisableBackground();
		}
		SetCustomDepth(FoundStencilMap->StencilValue);
	}
	else
	{
		DisableAura();
		DisableBackground();
	}
}

void ADBDObject::EnableAura()
{
	if (IsValid(ObjectMesh))
	{
		ObjectMesh->SetRenderCustomDepth(true);
		ObjectMesh->SetCustomDepthStencilWriteMask(ERendererStencilMask::ERSM_255);
		//ObjectMesh->SetCustomDepthStencilWriteMask(ERendererStencilMask::ERSM_1);
	}
}

void ADBDObject::EnableBackground()
{
	if (IsValid(WidgetComponent))
	{
		//WidgetComponent->SetVisibility(true);
	}
	if (IsValid(AuraMesh))
	{
		//AuraMesh->SetVisibility(true);
		//AuraMesh->SetCustomDepthStencilValue(0);
		//AuraMesh->SetCustomDepthStencilWriteMask(ERendererStencilMask::ERSM_128);
		//AuraMesh->SetRenderCustomDepth(true);
	}
}

void ADBDObject::DisableAura()
{
	if (IsValid(ObjectMesh))
	{
		ObjectMesh->SetRenderCustomDepth(false);
	}
}

void ADBDObject::DisableBackground()
{
	if (IsValid(WidgetComponent))
	{
		//WidgetComponent->SetVisibility(false);
	}
	if (IsValid(AuraMesh))
	{
		//AuraMesh->SetVisibility(false);
		//AuraMesh->SetRenderCustomDepth(false);
	}
}

void ADBDObject::SetCustomDepth(int32 value)
{
	if (ObjectMesh)
	{
		ObjectMesh->SetCustomDepthStencilValue(value);
	}
}


// Called when the game starts or when spawned
void ADBDObject::BeginPlay()
{
	Super::BeginPlay();
	if (ObjAbilitySystemComponent)
	{
		ObjAbilitySystemComponent->InitAbilityActorInfo(this, this);
		ObjAbilitySystemComponent->SetIsReplicated(true);
		ObjAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
		ObjAbilitySystemComponent->ServerSideInit();
	}
	Init();
}

void ADBDObject::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ADBDObject, bIsDestroyed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ADBDObject, StencilMaps, COND_None, REPNOTIFY_Always);
	//DOREPLIFETIME_CONDITION_NOTIFY(ADBDObject, Entity, COND_None, REPNOTIFY_Always);
	
}

// Called every frame
void ADBDObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADBDObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (WidgetComponent)
	{
		WidgetComponent->SetupAttachment(GetRootComponent());
	}
}

AObj_Entity* ADBDObject::GetEntity() const
{
	return Entity;
}

UInteractableComponent* ADBDObject::GetInteractableComponent() const
{
	if (InteractableComponent)
	{
		return InteractableComponent;
	}
	return nullptr;
}

void ADBDObject::SetDestroyed()
{
	bIsDestroyed = true;

	OnRep_IsDestroyed();
}

void ADBDObject::OnRep_IsDestroyed()
{
}


const TArray<FMotionWarpingInfo> ADBDObject::GetMotionWarpingTargets_Implementation()
{
	return ObjectMotionWarpingTargetInfos;
}
