// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/GAS/ObjAbilitySystemComponent.h"
#include "MMJ/Object/Widget/ObjWidgetBase.h"
#include "Obj_Progress.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UObj_Progress : public UObjWidgetBase
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;

	UPROPERTY()
	float ProgressBarWidth;

	UPROPERTY()
	float ProgressBarHeight;

	// 현재 진행도 업데이트
	void UpdateCurrentValue(const FOnAttributeChangeData& ChangeData);

	// 최대 진행도 업데이트
	void UpdateMaxValue(const FOnAttributeChangeData& ChangeData);
	
	float CachedCurrentValue;
	float CachedMaxValue;

	UFUNCTION()
	void SetDisplay(bool IsDisplay);
	
	// ASC 바인딩
	UFUNCTION(BlueprintCallable)
	void SetObjectASC(UObjAbilitySystemComponent* ASC,
		const FGameplayAttribute& CurrentAttribute, const FGameplayAttribute& MaxAttribute);

	void UpdateValue(float CurrentValue, float MaxValue);
private:
	UPROPERTY()
	UObjAbilitySystemComponent* ObjASC;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UProgressBar* ProgressBar;
	
};
