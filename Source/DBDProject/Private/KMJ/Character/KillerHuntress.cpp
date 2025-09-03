// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/Character/KillerHuntress.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KMJ/AbilitySystem/KillerAttributeSet.h"
 
AKillerHuntress::AKillerHuntress()
{
	if (KillerAttributeSet) KillerAttributeSet->ConditionalBeginDestroy();
	KillerAttributeSet = CreateDefaultSubobject<UKillerAttributeSet>(TEXT("HuntressAttributeSet"));
	if (KillerAttributeSet)
	{
		AKillerHuntress::InitKillerAttribute();
	}
}

void AKillerHuntress::InitKillerAttribute()
{
	GetCharacterMovement()->MaxWalkSpeed = KillerAttributeSet->WalkingSpeed.GetCurrentValue();
}
