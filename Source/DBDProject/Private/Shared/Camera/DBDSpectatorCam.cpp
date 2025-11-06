// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Camera/DBDSpectatorCam.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ADBDSpectatorCam::ADBDSpectatorCam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SetRootComponent(SpringArmComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->TargetOffset = FVector(0.0f, 0.0f, 0.0f);
	//SpringArmComponent->SetWorldRotation(FRotator(0.f, 180.f, 0.f));
}

// Called when the game starts or when spawned
void ADBDSpectatorCam::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADBDSpectatorCam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

