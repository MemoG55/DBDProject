// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/UI/SkillCheckModalWidget.h"

#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/ProgressBar.h"
#include "Components/TimelineComponent.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "JMS/Component/SkillCheckComponent.h"


void USkillCheckModalWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void USkillCheckModalWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ASurvivorCharacter* OwningSurvivor = Cast<ASurvivorCharacter>(GetOwningPlayerPawn());
	if (OwningSurvivor)
	{
		OwnerSkillCheckComponent = OwningSurvivor->FindComponentByClass<USkillCheckComponent>();
	}
}


void USkillCheckModalWidget::SkillCheckNeedleUpdate(float Output)
{
	CurrentTime = Output;
	float CurrentTimeToDegree = CurrentTime * 360 - 180;
	if (Needle)
	{
		Needle->SetRenderTransformAngle(CurrentTimeToDegree);
	}
}

void USkillCheckModalWidget::Activate(float InDuration, float InGoodWindowLength, float InGoodWindowStart,
                                      float InGreatWindowLength)
{
	SetVisibility(ESlateVisibility::Visible);
	Duration = InDuration;
	GoodWindowLength = InGoodWindowLength;
	GoodWindowStart = InGoodWindowStart;
	GreatWindowLength = InGreatWindowLength;

	if (Duration <= 0)
	{
		Deactivate();
		return;
	}
	float GoodStartRatio = GoodWindowStart / Duration;
	float GoodEndRatio = (GoodWindowLength + GoodWindowStart) / Duration;
	float GoodLengthRatio = GoodWindowLength/Duration;
	float GreatEndRatio = (GreatWindowLength + GoodWindowStart) / Duration;
	float GreatLengthRatio = GreatWindowLength/Duration;
	float GoodStartRatioToDegree = GoodStartRatio * 360 - 180;
	float GoodEndRatioToDegree = GoodEndRatio * 360 - 180;

	if (OwnerSkillCheckComponent)
	{
		OwnerSkillCheckComponent->SkillCheckEndDelegate.AddDynamic(
			this, &USkillCheckModalWidget::PlayAnimationAndDeactivate);
	}

	if (SuccessRing)
	{
		UMaterialInstanceDynamic* SucceessRingMID = SuccessRing->GetDynamicMaterial();
		if (SucceessRingMID)
		{
			SucceessRingMID->SetScalarParameterValue(FName("StartPercent"), -GoodStartRatio);
			SucceessRingMID->SetScalarParameterValue(FName("EndPercent"), GoodLengthRatio);
		}
	}
	if (BonusRing)
	{
		UMaterialInstanceDynamic* BonusRingMID = BonusRing->GetDynamicMaterial();
		if (BonusRingMID)
		{
			BonusRingMID->SetScalarParameterValue(FName("StartPercent"), -GoodStartRatio);
			BonusRingMID->SetScalarParameterValue(FName("EndPercent"), GreatLengthRatio);
		}
	}
	if (StartSection)
	{
		StartSection->SetRenderTransformAngle(GoodStartRatioToDegree);
	}
	if (EndSection)
	{
		EndSection->SetRenderTransformAngle(GoodEndRatioToDegree);
	}
}

void USkillCheckModalWidget::Deactivate()
{
	SetVisibility(ESlateVisibility::Hidden);
	if (OwnerSkillCheckComponent->SkillCheckEndDelegate.IsBound())
	{
		OwnerSkillCheckComponent->SkillCheckEndDelegate.RemoveDynamic(
			this, &USkillCheckModalWidget::PlayAnimationAndDeactivate);
	}
}

void USkillCheckModalWidget::PlayAnimationAndDeactivate(ESkillCheckResult InResult)
{
	UE_LOG(LogTemp, Warning, TEXT("JMS : Deactivate SkillCheckWidget - TODO: Add Animation"));
	Deactivate();
}
