// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/ObjFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Character/DBDCharacter.h"

bool UObjFunctionLibrary::ActorHasGameplayTag(AActor* Actor, FGameplayTag Tag)
{
	UAbilitySystemComponent* ASC = NativeGetAbilitySystemComponent(Actor);
	if (ASC)
	{
		return ASC->HasMatchingGameplayTag(Tag);
	}
	return false;
}

UAbilitySystemComponent* UObjFunctionLibrary::NativeGetAbilitySystemComponent(AActor* Actor)
{
	check(Actor);

	return UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);
}

float UObjFunctionLibrary::GetStaticCooldownDurationForAbility(const UGameplayAbility* Ability)
{
	if (!Ability) return 0.f;

	const UGameplayEffect* CooldownEffect = Ability->GetCooldownGameplayEffect();
	if (!CooldownEffect) return 0.f;

	float CooldownDuration = 0.f;
	CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1, CooldownDuration);
	return CooldownDuration;
}

float UObjFunctionLibrary::GetStaticCostForAbility(const class UGameplayAbility* Ability)
{
	if (!Ability) return 0.f;

	const UGameplayEffect* CostEffect = Ability->GetCostGameplayEffect();
	if (!CostEffect) return 0.f;

	float Cost = 0.f;
	CostEffect->Modifiers[0].ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Cost);
	return FMath::Abs(Cost);
}

FGameplayTag UObjFunctionLibrary::ComputeInteractDirection(const AActor* Object, const AActor* Interactor)
{
	const FVector ObjectForward = Object->GetActorForwardVector();
	const FVector ObjectToInteractorNormalized = (Interactor->GetActorLocation() - Object->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(ObjectForward, ObjectToInteractorNormalized);
	float OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(ObjectForward, ObjectToInteractorNormalized);

	if (CrossResult.Z < 0.f)
	{
		OutAngleDifference *= -1.f;
	}
 
	if (OutAngleDifference >= -45.f && OutAngleDifference <= 45.f)
	{
		return DBDGameplayTags::Shared_Direction_Front;
	}
	else if (OutAngleDifference < -45.f && OutAngleDifference >= -135.f)
	{
		return DBDGameplayTags::Shared_Direction_Left;
	}
	else if (OutAngleDifference < -135.f || OutAngleDifference > 135.f)
	{
		return DBDGameplayTags::Shared_Direction_Back;
	}
	else if (OutAngleDifference > 45.f && OutAngleDifference <= 135.f)
	{
		return DBDGameplayTags::Shared_Direction_Right;
	}
	return FGameplayTag();
}

EPlayerRole UObjFunctionLibrary::GetPlayerRole(const AActor* Actor)
{
	// Actor가 살인마인지, 생존자인지 판별하는 로직 필요 
	if (const ADBDCharacter* Character = Cast<ADBDCharacter>(Actor))
	{
		if (APlayerController* PC = Cast<APlayerController>(Character->GetController()))
		{
			if (ADBDPlayerState* PS = PC->GetPlayerState<ADBDPlayerState>())
			{
				return PS->GetPlayerRole();
			}
		}
	}
	return EPlayerRole();
}

bool UObjFunctionLibrary::IsSurvivor(const AActor* Actor)
{
	if (GetPlayerRole(Actor) == EPlayerRole::Survivor)
	{
		return true;
	}
	return false;
}

bool UObjFunctionLibrary::IsKiller(const AActor* Actor)
{
	if (GetPlayerRole(Actor) == EPlayerRole::Killer)
	{
		return true;
	}
	return false;
}
