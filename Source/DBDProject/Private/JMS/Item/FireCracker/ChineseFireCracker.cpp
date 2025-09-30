// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Item/FireCracker/ChineseFireCracker.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "JMS/GAS/ItemAbilitySystemComponent.h"
#include "JMS/GAS/SurvivorAbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/GAS/GE/GE_GrantBlindTagForDuration.h"

AChineseFireCracker::AChineseFireCracker()
{
	ItemTag = DBDGameplayTags::Survivor_Item_FireCracker;
}

void AChineseFireCracker::OnEquipItem()
{
	Super::OnEquipItem();
}

void AChineseFireCracker::OnInitialized_Implementation()
{
	Super::OnInitialized_Implementation();
}

void AChineseFireCracker::OnItemUsed()
{
	Super::OnItemUsed();
	if (GetOwner()->HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimer(ExplodeTimerHandle, this, &AChineseFireCracker::Explode,
		                                       ExplodeDelay,
		                                       false);
	}
}

void AChineseFireCracker::Explode()
{
	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> HitResults;
	ETraceTypeQuery TraceTypeQuery = UCollisionProfile::Get()->ConvertToTraceType(ECollisionChannel::ECC_Pawn);
	UKismetSystemLibrary::SphereTraceMulti(GetWorld(), GetActorLocation(), GetActorLocation(),
										   ExplodeRadius,
										   TraceTypeQuery, false, ActorsToIgnore, EDrawDebugTrace::Type::ForDuration,
										   HitResults, true, FLinearColor::Red, FLinearColor::Green, 0.1);


	for (const FHitResult& HitResult : HitResults)
	{
		IAbilitySystemInterface* ASInterface = Cast<IAbilitySystemInterface>(HitResult.GetActor());
		if (!ASInterface)
		{
			continue;
		}

		UDBDAbilitySystemComponent* ASC = Cast<UDBDAbilitySystemComponent>(
			ASInterface->GetAbilitySystemComponent());
		if (ASC)
		{
			ItemAbilitySystemComponent->BP_ApplyGameplayEffectToTarget(
				UGE_GrantBlindTagForDuration::StaticClass(), ASC, 0, ItemAbilitySystemComponent->MakeEffectContext());
		}
	}
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
}
