// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Interactable/DBDObject.h"

#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "JMS/GAS/SurvivorAttributeSet.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MMJ/Object/AnimInstance/DBDObjectAnimInstance.h"
#include "MMJ/Object/GAS/ObjAbilitySystemComponent.h"
#include "MMJ/Object/GAS/ObjAttributeSet.h"
#include "MMJ/Object/Widget/Obj_HUD.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Component/InteractableComponent.h"

FName ADBDObject::InteractableComponentName = TEXT("InteractableComponent");

// Sets default values
ADBDObject::ADBDObject(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bAlwaysRelevant = true;
	bReplicates = true;
	//bNetLoadOnClient = false;
	
	ObjectMesh = CreateDefaultSubobject<USkeletalMeshComponent>("ObjectMesh");
	ObjectMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	ObjectMesh->SetCollisionObjectType(ECC_WorldStatic);
	SetRootComponent(ObjectMesh);


	ObjAbilitySystemComponent = CreateDefaultSubobject<UObjAbilitySystemComponent>("ObjAbilitySystemComponent");
	ObjAttributeSet = CreateDefaultSubobject<UObjAttributeSet>("ObjAttributeSet");

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(InteractableComponentName);
	InteractableComponent->SetupAttachment(GetRootComponent());
	InteractableComponent->SetCollisionProfileName(FName("InteractionOnly"));
	//InteractableComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	//InteractableComponent->SetCollisionObjectType(ECC_WorldDynamic);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Widget");
	WidgetComponent->SetupAttachment(GetRootComponent());
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen); // 스크린 공간
	WidgetComponent->SetDrawSize(FVector2D(10.0f, 3.0f));
}

UAbilitySystemComponent* ADBDObject::GetAbilitySystemComponent() const
{
	return ObjAbilitySystemComponent;
}

void ADBDObject::Init()
{
	if (WidgetComponent)
	{
		ObjHUD = Cast<UObj_HUD>(WidgetComponent->GetUserWidgetObject());
		if (ObjHUD && ObjAbilitySystemComponent)
		{
			ObjHUD->ConfigureASC(ObjAbilitySystemComponent);
		}
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

UInteractableComponent* ADBDObject::GetInteractableComponent() const
{
	if (InteractableComponent)
	{
		return InteractableComponent;
	}
	return nullptr;
}

USkeletalMeshComponent* ADBDObject::GetSkeletalMeshComponent() const
{
	return ObjectMesh;
}