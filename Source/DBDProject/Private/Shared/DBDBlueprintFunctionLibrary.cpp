// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/DBDBlueprintFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Shared/GAS/DBDAbilitySystemComponent.h"

UDBDAbilitySystemComponent* UDBDBlueprintFunctionLibrary::NativeGetAbilitySystemComponentFromActor(AActor* Actor)
{
	check(Actor);

	return CastChecked<UDBDAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor));
}

void UDBDBlueprintFunctionLibrary::AddUniqueTagToActor(AActor* Actor, FGameplayTag Tag)
{
	UDBDAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);
	
	if (!ASC->HasMatchingGameplayTag(Tag))
	{
		ASC->AddReplicatedLooseGameplayTag(Tag);
	}
}


void UDBDBlueprintFunctionLibrary::RemoveTagFromActor(AActor* Actor, FGameplayTag Tag)
{
	UDBDAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);

	
	if (ASC->HasMatchingGameplayTag(Tag))
	{
		ASC->RemoveReplicatedLooseGameplayTag(Tag);
	}
}

bool UDBDBlueprintFunctionLibrary::NativeActorHasTag(AActor* Actor, FGameplayTag Tag)
{
	UDBDAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);
	return ASC->HasMatchingGameplayTag(Tag);
}

void UDBDBlueprintFunctionLibrary::BP_HasTag(AActor* Actor, FGameplayTag Tag, EBaseConfirmType& OutType)
{
	OutType = NativeActorHasTag(Actor, Tag) ? EBaseConfirmType::Yes : EBaseConfirmType::No;
}
