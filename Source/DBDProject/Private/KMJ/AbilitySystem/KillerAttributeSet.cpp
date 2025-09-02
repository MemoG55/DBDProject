// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/AbilitySystem/KillerAttributeSet.h"


UKillerAttributeSet::UKillerAttributeSet()
{
	InitWalkingSpeed(4.6f);
	InitStunRate(1.f);
	InitPickUpSpeedRate(1.f);
	InitTerrorRadiusRange(32.f);
	InitDestroyPalletRate(1.f);
	InitDamageGeneratorRange(1.f);
}
