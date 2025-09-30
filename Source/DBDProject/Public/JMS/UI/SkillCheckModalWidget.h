// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MMJ/Object/Widget/ObjWidgetBase.h"
#include "SkillCheckModalWidget.generated.h"

class UOverlay;
enum class ESkillCheckResult : uint8;
class UTimelineComponent;
class USkillCheckComponent;
class UImage;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API USkillCheckModalWidget : public UObjWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	UFUNCTION()
	void SkillCheckNeedleUpdate(float Output);
	void Activate(float InDuration, float InGoodWindowLength, float InGoodWindowStart, float InGreatWindowLength);
	void Deactivate();

	UFUNCTION()
	void PlayAnimationAndDeactivate(ESkillCheckResult InResult);
private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* Button;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* SuccessRing;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* BonusRing;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UOverlay* Needle;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UOverlay* Ring;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UOverlay* StartSection;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UOverlay* EndSection;
	
	UPROPERTY()
	USkillCheckComponent* OwnerSkillCheckComponent;

	float Duration;
	float GoodWindowLength;
	float GoodWindowStart;
	float GreatWindowLength;
	float CurrentTime;
};
