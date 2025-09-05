// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/Character/KillerHuntress.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KMJ/AbilitySystem/HuntressAttributeSet.h"
#include "KMJ/AbilitySystem/KillerAttributeSet.h"
 
AKillerHuntress::AKillerHuntress()
{
	/*if (KillerAttributeSet) KillerAttributeSet->ConditionalBeginDestroy();
	// KillerAttributeSet이 없거나 삭제된 경우에만 새로 생성
	if (!KillerAttributeSet) KillerAttributeSet = CreateDefaultSubobject<UKillerAttributeSet>(TEXT("KillerAttributeSet"));*/
	HuntressAttributeSet = CreateDefaultSubobject<UHuntressAttributeSet>(TEXT("HuntressAttributeSet"));
}

void AKillerHuntress::InitHuntressAttribute()
{
	
}


/*UAbilitySystemComponent* AKillerHuntress::GetAbilitySystemComponent() const
{
	return Super::GetAbilitySystemComponent();
}*/

void AKillerHuntress::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AKillerHuntress::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AKillerHuntress::PawnClientRestart()
{
	Super::PawnClientRestart();
}

void AKillerHuntress::ServerSideInit()
{
	Super::ServerSideInit();
}

void AKillerHuntress::ClientSideInit()
{
	Super::ClientSideInit();
}

void AKillerHuntress::OnAbilityGranted()
{
	/*if (KillerAttributeSet)
	{
		AKillerHuntress::InitKillerAttribute();
	}*/
}
