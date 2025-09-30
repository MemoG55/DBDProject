// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Item/SurvivorItem.h"

#include "JMS/Component/ItemInteractableComponent.h"
#include "JMS/GAS/ItemAbilitySystemComponent.h"
#include "JMS/ItemAddon/ItemAddonComponent.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/Component/InteractableComponent.h"

ASurvivorItem::ASurvivorItem()
{
	NetUpdateFrequency = 10.f;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionProfileName("NoCollision");

	ItemInteractableComponent = CreateDefaultSubobject<UItemInteractableComponent>(TEXT("ItemInteractableComponent"));
	ItemInteractableComponent->SetupAttachment(Mesh);
	ItemInteractableComponent->SetCollisionProfileName("InteractionOnly");
	ItemInteractableComponent->SetBoxExtent(FVector(150.f, 150.f, 150.f));

	ItemAbilitySystemComponent = CreateDefaultSubobject<
		UItemAbilitySystemComponent>(TEXT("ItemAbilitySystemComponent"));
}

UInteractableComponent* ASurvivorItem::GetInteractableComponent() const
{
	return ItemInteractableComponent;
}

UAbilitySystemComponent* ASurvivorItem::GetAbilitySystemComponent() const
{
	return ItemAbilitySystemComponent;
}

void ASurvivorItem::AttachAddon1(UItemAddonComponent* InAddon1)
{
	if (InAddon1)
	{
		Addon1 = InAddon1;
		Addon1->RegisterComponent();
	}
}

void ASurvivorItem::AttachAddon2(UItemAddonComponent* InAddon2)
{
	if (InAddon2)
	{
		Addon2 = InAddon2;
		Addon2->RegisterComponent();
	}
}

void ASurvivorItem::OnInitialized_Implementation()
{
	if (Addon1)
	{
		Addon1->OnInitialized();
	}
	if (Addon2)
	{
		Addon2->OnInitialized();
	}
	// 자식에서 구현하되 Super를 마지막에 호출합니다.	
}

void ASurvivorItem::OnEquipItem()
{
	ItemInteractableComponent->SetInteractable(false);
	IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(GetOwner());
	if (ASI)
	{
		UDBDBlueprintFunctionLibrary::AddUniqueTagToActor(GetOwner(),ItemTag);
	}
	OnInitialized();
}

void ASurvivorItem::OnItemUsed()
{
}

void ASurvivorItem::OnDropItem()
{
	ItemInteractableComponent->SetInteractable(true);
	IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(GetOwner());
	if (ASI)
	{
		UDBDBlueprintFunctionLibrary::RemoveTagFromActor(GetOwner(),ItemTag);
	}
}

USkeletalMeshComponent* ASurvivorItem::GetMesh() const
{
	return Mesh;
}

FName ASurvivorItem::GetItemID() const
{
	return ItemID;
}

UItemAddonComponent* ASurvivorItem::GetAddon1() const
{
	return Addon1;
}

UItemAddonComponent* ASurvivorItem::GetAddon2() const
{
	return Addon2;
}

// 오류시 더 앞쪽으로 이동
void ASurvivorItem::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);
	SetReplicateMovement(true);
	ItemAbilitySystemComponent->InitAbilityActorInfo(this,this);
}
