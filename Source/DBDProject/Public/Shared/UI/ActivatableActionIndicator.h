// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "ActivatableActionIndicator.generated.h"

class UDBDAbilitySystemComponent;
/**
 * 
 */

UCLASS()
class DBDPROJECT_API UActivatableActionIndicator : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY()
	UDBDAbilitySystemComponent* OwnerDBDCharacterASC;
	virtual void NativeConstruct() override;


	UPROPERTY(EditDefaultsOnly, Category = "AbilityIndicator")
	FGameplayTag VisibleTag;
	UPROPERTY(EditDefaultsOnly, Category = "AbilityIndicator")
	FGameplayTagContainer HideTags;
	void OnVisibleTagChanged(const FGameplayTag Tag, int32 NewCount);
	void OnHideTagChanged(const FGameplayTag Tag, int32 NewCount);
public:
	
};
