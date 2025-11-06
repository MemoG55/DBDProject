// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DBDProgressBarBase.generated.h"

struct FGameplayAttribute;
struct FOnAttributeChangeData;
class UImage;
class UProgressBar;
/**
 * 진행도 게이지 또는 탈출구 개방 타이머와 같은 ProgressBar가 들어가는 위젯의 공용 베이스 위젯
 */
UCLASS()
class DBDPROJECT_API UDBDProgressBarBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void Display();
	
	// 현재 정보 저장 변수
	float CachedCurrentValue;
	float CachedMaxValue;
	float CachedPercent;

	// ASC에 연동하여 사용할 경우 캐시 변수
	UPROPERTY()
	class UDBDAbilitySystemComponent* OwnerASC;

public:
	// ASC 바인딩
	UFUNCTION(BlueprintCallable)
	virtual void SetObjectASC(UDBDAbilitySystemComponent* ASC,
		const FGameplayAttribute& CurrentAttribute, const FGameplayAttribute& MaxAttribute);

	// AttributeSet에 기반할 경우 델리게이트 연결할 함수
	virtual void UpdateCurrentValueByAttribute(const FOnAttributeChangeData& ChangeData);
	// AttributeSet에 기반할 경우 델리게이트 연결할 함수
	virtual void UpdateMaxValueByAttribute(const FOnAttributeChangeData& ChangeData);

	// 단순 float변수로 받아올 경우 델리게이트 연결할 함수
	UFUNCTION()
	virtual void UpdateCurrentValue(float NewValue);
	// 단순 float변수로 받아올 경우 델리게이트 연결할 함수
	UFUNCTION()
	virtual void UpdateMaxValue(float NewValue);

protected:
	// 최종 Progressbar Update함수
	virtual void Update();

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UProgressBar* ProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* BaseProgressBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* BaseProgressFill;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* CurrentProgressMarking;


};
