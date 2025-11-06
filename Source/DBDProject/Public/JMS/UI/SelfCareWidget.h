// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/UI/AbilityWidgetBase.h"
#include "SelfCareWidget.generated.h"

struct FOnAttributeChangeData;
class UProgressBar;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API USelfCareWidget : public UAbilityWidgetBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* ProgressBar;
	
	virtual void OnAbilityActivated(UGameplayAbility* Ability) override;
	virtual void OnAbilityDeactivated(UGameplayAbility* Ability) override;

	
private:
	void SetPercent(float Percent);

	void AttributeChanged(const FOnAttributeChangeData& Data);

	float CachedMaxValue;

	FDelegateHandle AttributeChangedDelegateHandle;
public:
	virtual void NativeConstruct() override;
	
};
