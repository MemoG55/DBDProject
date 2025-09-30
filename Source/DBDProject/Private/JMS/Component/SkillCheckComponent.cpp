// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Component/SkillCheckComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "IMediaControls.h"
#include "Blueprint/UserWidget.h"
#include "Components/TimelineComponent.h"
#include "JMS/UI/SkillCheckModalWidget.h"
#include "Shared/DBDDebugHelper.h"


USkillCheckComponent::USkillCheckComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsSkillCheckDone = true;
}

void USkillCheckComponent::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* OwningPlayerController = Cast<APlayerController>(GetOwningController());
	if (OwningPlayerController && OwningPlayerController->IsLocalPlayerController())
	{
		SkillCheckWidget = CreateWidget<USkillCheckModalWidget>(OwningPlayerController, SkillCheckWidgetClass);
		if (SkillCheckWidget)
		{
			SkillCheckWidget->AddToViewport();
			SkillCheckWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	// SkillCheckTimeline = NewObject<UTimelineComponent>(this, FName("SkillCheckTimeline"));
	// SkillCheckTimeline->RegisterComponent();
	//
	// TimelineUpdateDelegate.BindUFunction(this, FName("TimelineUpdate"));
	// SkillCheckTimeline->AddInterpFloat(SkillCheckTimelineCurve, TimelineUpdateDelegate);
	//
	// TimelineFinishedDelegate.BindUFunction(this, FName("TimelineFinished"));
	// SkillCheckTimeline->SetTimelineFinishedFunc(TimelineFinishedDelegate);
	SetComponentTickEnabled(false);
}

void USkillCheckComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CurrentTime += DeltaTime;
	if (SkillCheckWidget&&CachedDuration>0)
	{
		SkillCheckWidget->SkillCheckNeedleUpdate(CurrentTime/CachedDuration);
	}
	if (CurrentTime>CachedDuration)
	{
		OnEndSkillCheck();
	}
	Debug::Print(TEXT("JMS13 : CurrentTime : "), CurrentTime, 13);
}


void USkillCheckComponent::TriggerOneShotSkillCheck(float Duration, float GoodWindowStart, float GoodWindowLength,
                                                    float GreatWindowLength)
{
	bIsSkillCheckDone = false;
	SetComponentTickEnabled(true);
	CurrentTime = 0;
	CachedDuration = Duration;
	CachedGoodWindowStart = GoodWindowStart;
	CachedGoodWindowLength = GoodWindowLength;
	CachedGreatWindowLength = GreatWindowLength;
	APlayerController* PC = Cast<APlayerController>(GetOwningController());
	if (PC && PC->IsLocalPlayerController())
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = PC->GetLocalPlayer()->GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>();
		if (InputSubsystem)
		{
			InputSubsystem->AddMappingContext(SkillCheckIMC, SkillCheckIMCPriority);
		}
	}
	if (Duration < 0)
	{
		return;
	}
	// SkillCheckTimeline->SetPlayRate(1.f / Duration);
	if (SkillCheckWidget)
	{
		SkillCheckWidget->Activate(Duration, GoodWindowLength, GoodWindowStart, GreatWindowLength);
	}
	// SkillCheckTimeline->PlayFromStart();
}

void USkillCheckComponent::CancelSkillCheck()
{
	APlayerController* PC = Cast<APlayerController>(GetOwningController());
	if (PC && PC->IsLocalPlayerController())
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = PC->GetLocalPlayer()->GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>();
		if (InputSubsystem)
		{
			InputSubsystem->RemoveMappingContext(SkillCheckIMC);
		}
	}
	//Debug::Print(TEXT("JMS14 : SkillCheckEnd"), GetOwnerRole(), 14);
	SetComponentTickEnabled(false);
	if (SkillCheckWidget)
	{
		SkillCheckWidget->Deactivate();
	}
}

void USkillCheckComponent::OnEndSkillCheck()
{
	// bIsSkillCheckDone = true;
	// SkillCheckTimeline->Stop();
	// float TimelinePlaybackPosition = SkillCheckTimeline->GetPlaybackPosition();
	// float StopTime = TimelinePlaybackPosition * CachedDuration;
	// if (StopTime > CachedGoodWindowStart && StopTime < CachedGoodWindowStart +
	// 	CachedGoodWindowLength)
	// {
	// 	if (StopTime < CachedGoodWindowStart + CachedGreatWindowLength)
	// 	{
	// 		CachedResult = ESkillCheckResult::Great;
	// 	}
	// 	else
	// 	{
	// 		CachedResult = ESkillCheckResult::Good;
	// 	}
	// }
	// else
	// {
	// 	CachedResult = ESkillCheckResult::Bad;
	// }
	if (CurrentTime > CachedGoodWindowStart && CurrentTime < CachedGoodWindowStart +
		CachedGoodWindowLength)
	{
		if (CurrentTime < CachedGoodWindowStart + CachedGreatWindowLength)
		{
			CachedResult = ESkillCheckResult::Great;
		}
		else
		{
			CachedResult = ESkillCheckResult::Good;
		}
	}
	else
	{
		CachedResult = ESkillCheckResult::Bad;
	}
	SkillCheckEndDelegate.Broadcast(CachedResult);
	APlayerController* PC = Cast<APlayerController>(GetOwningController());
	if (PC && PC->IsLocalPlayerController())
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = PC->GetLocalPlayer()->GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>();
		if (InputSubsystem)
		{
			InputSubsystem->RemoveMappingContext(SkillCheckIMC);
		}
	}
	//Debug::Print(TEXT("JMS14 : SkillCheckEnd"), GetOwnerRole(), 14);
	SetComponentTickEnabled(false);
	if (SkillCheckWidget)
	{
		SkillCheckWidget->Deactivate();
	}
}

void USkillCheckComponent::SetupInputActionBinding(UEnhancedInputComponent* EnhancedInputComponent)
{
	if (EnhancedInputComponent && SkillCheckInputAction)
	{
		EnhancedInputComponent->BindAction(SkillCheckInputAction, ETriggerEvent::Triggered, this,
		                                   &USkillCheckComponent::SkillCheckConfirm);
	}
}

void USkillCheckComponent::SkillCheckConfirm(const FInputActionValue& InputActionValue)
{
	bool bConfirm = InputActionValue.Get<bool>();
	if (bConfirm)
	{
		OnEndSkillCheck();
	}
}
//
// void USkillCheckComponent::TimelineUpdate(float Value)
// {
// 	if (!bIsSkillCheckDone)
// 	{
// 		if (SkillCheckWidget)
// 		{
// 			SkillCheckWidget->SkillCheckNeedleUpdate(Value);
// 		}
// 		//Debug::Print(TEXT("JMS12 : TimelineUpdate - Value : "), Value, 12);
// 		//Debug::Print(TEXT("JMS14 : SkillCheckDone is false"), 14);
// 	}
// 	else
// 	{
// 		//Debug::Print(TEXT("JMS14 : SkillCheckDone is true"), 14);
// 	}
// }
//
// void USkillCheckComponent::TimelineFinished()
// {
// 	if (!bIsSkillCheckDone)
// 	{
// 		//Debug::Print(TEXT("JMS14 : SkillCheckDone is false"), 14);
// 		OnEndSkillCheck();
// 	}
// 	else
// 	{
// 		//Debug::Print(TEXT("JMS14 : SkillCheckDone is true"), 14);
// 	}
// }
