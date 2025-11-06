// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/AnimInstances/KillerAnimInstance.h"
#include "Gameframework/Character.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "KMJ/Character/KillerCharacter.h"
#include "Net/UnrealNetwork.h"

void UKillerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	//애니메이션에서 사용할 캐릭터, 캐릭터 무브먼트 캐시
	KillerOwnerCharacter = Cast<AKillerCharacter>(TryGetPawnOwner());
	if (KillerOwnerCharacter)
	{
		KillerOwnerMovementComponent = KillerOwnerCharacter->GetCharacterMovement();
	}
}

void UKillerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (KillerOwnerCharacter)
	{
		KillerSpeed = KillerOwnerCharacter->GetVelocity().Length();
	}
}
void UKillerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	if (!KillerOwnerCharacter)
	{
		//Debug::Print(TEXT("PlayerAnimInstance : Can't find PlayerCharacter by Update"),FColor::Red,1000);
		return;
	}
	//KillerAim_Horizontal = FRotator::NormalizeAxis(KillerOwnerCharacter->KillerAim_Horizontal);
	if (KillerOwnerCharacter->IsLocallyControlled())
	{
		KillerAim_Horizontal = FMath::ClampAngle(KillerOwnerCharacter->GetControlRotation().Pitch, -90.0f, 90.0f);
	}
	else
	{
		KillerAim_Horizontal = FRotator::NormalizeAxis(KillerOwnerCharacter->KillerAim_Horizontal);	
	}
}

void UKillerAnimInstance::InitializeWithAbilitySystem(UAbilitySystemComponent* ASC)
{
	Super::InitializeWithAbilitySystem(ASC);
}

void UKillerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}
