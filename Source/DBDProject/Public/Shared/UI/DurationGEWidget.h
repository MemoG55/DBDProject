// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "DurationGEWidget.generated.h"

class UAbilitySystemComponent;
struct FGameplayEffectSpec;
struct FActiveGameplayEffectHandle;
class UBaseIcon;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDurationGEWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY(EditDefaultsOnly, Category = "DurationGEWidget")
	FGameplayTag DurationTag;
	
	UPROPERTY(meta = (BindWidget))
	UBaseIcon* EffectIcon;

	void OnDurationTagChanged(const FGameplayTag Tag, int32 NewCount);

	FTimerHandle DurationUpdateTimer;
	void UpdateDuration();
	UPROPERTY()
	UAbilitySystemComponent* CachedOwnerASC;
};
