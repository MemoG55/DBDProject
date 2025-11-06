// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityWidgetBase.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UAbilityWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category="Ability",meta = (AllowPrivateAccess = "true"))
	UClass* GameplayAbilityClass;

	virtual void OnAbilityActivated(UGameplayAbility* Ability);
	virtual void OnAbilityDeactivated(UGameplayAbility* Ability);

	UPROPERTY()
	UAbilitySystemComponent* OwnerASC;
	UPROPERTY()
	APawn* OwningPlayerPawn;
public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;	
	
	
	
};
