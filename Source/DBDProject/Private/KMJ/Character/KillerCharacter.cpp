// Fill out your copyright notice in the Description page of Project Settings.

#include "KMJ/Character/KillerCharacter.h"
#include "Camera/CameraComponent.h"

AKillerCharacter::AKillerCharacter()
{
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(GetMesh(), TEXT("Camera"));

	//메시 -90도 돌려놓아 정면으로 조정
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	//
}