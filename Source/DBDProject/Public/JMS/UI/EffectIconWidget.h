// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "EffectIconWidget.generated.h"

class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UEffectIconWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	UPROPERTY(EditDefaultsOnly, Category = "EffectIconWidget")
	FGameplayTag EffectTag;
	UPROPERTY(EditDefaultsOnly, Category = "EffectIconWidget")
	FGameplayTagContainer AdditionalAnyRequiredTags;
	UPROPERTY()
	UAbilitySystemComponent* CachedOwnerASC;

	void OnEffectTagChanged(const FGameplayTag Tag, int32 NewCount);
	void OnAdditionalAnyRequiredTagsChanged(const FGameplayTag Tag, int32 NewCount);
};
