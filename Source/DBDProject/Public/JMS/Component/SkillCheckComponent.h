// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Shared/Component/CharacterExtensionComponent.h"
#include "Shared/DBDEnum.h"
#include "SkillCheckComponent.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class USkillCheckModalWidget;
/**
 * Skill Check Component
 *
 * SkillCheckEndDelegate에 원하는 함수를 바인딩 한 후
 * TriggerOneShotSkillCheck를 호출해주세요
 * 
 * SkillCheckEndDelegate에 바인딩한 함수는 Good, Great, Bad 중 하나를 Enum으로 전달받습니다.
 *
 * TODO: 위젯 제작
 * TODO: 살인마용 스킬체크 제작
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSkillCheckResultDelegate, ESkillCheckResult, Result);

UCLASS()
class DBDPROJECT_API USkillCheckComponent : public UCharacterExtensionComponent
{
	GENERATED_BODY()

public:
	USkillCheckComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	void TriggerOneShotSkillCheck(float Duration, float GoodWindowStart, float GoodWindowLength,
	                              float GreatWindowLength);
	void CancelSkillCheck();
	void OnEndSkillCheck();
	void SetupInputActionBinding(UEnhancedInputComponent* EnhancedInputComponent);

	UPROPERTY(BlueprintAssignable, Category = "SkillCheck")
	FSkillCheckResultDelegate SkillCheckEndDelegate;
	FOnTimelineFloat TimelineUpdateDelegate;
	FOnTimelineEvent TimelineFinishedDelegate;

protected:
	void SkillCheckConfirm(const FInputActionValue& InputActionValue);

private:
	UPROPERTY(EditDefaultsOnly, Category = "SkillCheck", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> SkillCheckWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "SkillCheck", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* SkillCheckIMC;
	UPROPERTY(EditDefaultsOnly, Category = "SkillCheck", meta = (AllowPrivateAccess = "true"))
	int32 SkillCheckIMCPriority;
	UPROPERTY(EditDefaultsOnly, Category = "SkillCheck", meta = (AllowPrivateAccess = "true"))
	UInputAction* SkillCheckInputAction;

	UPROPERTY()
	USkillCheckModalWidget* SkillCheckWidget;

	UPROPERTY()
	UTimelineComponent* SkillCheckTimeline;
	// UFUNCTION()
	// void TimelineUpdate(float Value);
	// UFUNCTION()
	// void TimelineFinished();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* SkillCheckTimelineCurve;
	bool bIsSkillCheckDone;

	float CurrentTime = 0;


	float CachedDuration;
	float CachedGoodWindowStart;
	float CachedGoodWindowLength;
	float CachedGreatWindowLength;
	ESkillCheckResult CachedResult;
};
