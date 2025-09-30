// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/ItemAddon/ItemAddonComponent.h"

// Sets default values for this component's properties
UItemAddonComponent::UItemAddonComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemAddonComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UItemAddonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FName UItemAddonComponent::GetAddonID() const
{
	return AddonID;
}

void UItemAddonComponent::OnInitialized_Implementation()
{
	// 자식에서 구현
}

