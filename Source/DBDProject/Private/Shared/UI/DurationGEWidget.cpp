// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/DurationGEWidget.h"

#include "AbilitySystemComponent.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/UI/BaseIcon.h"


void UDurationGEWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ASurvivorCharacter* OwningPlayerPawn = Cast<ASurvivorCharacter>(GetOwningPlayerPawn());
	if (OwningPlayerPawn)
	{
		CachedOwnerASC = OwningPlayerPawn->GetAbilitySystemComponent();
		if (CachedOwnerASC)
		{
			CachedOwnerASC->RegisterGameplayTagEvent(DurationTag).AddUObject(
				this, &UDurationGEWidget::OnDurationTagChanged);
		}
	}
	SetVisibility(ESlateVisibility::Collapsed);
	EffectIcon->SetIconState(EIconEffect::Cooldown);
}


void UDurationGEWidget::OnDurationTagChanged(const FGameplayTag Tag, int32 NewCount)
{
	if (NewCount > 0)
	{
		SetVisibility(ESlateVisibility::Visible);
		UpdateDuration();
		GetWorld()->GetTimerManager().SetTimer(DurationUpdateTimer, this, &UDurationGEWidget::UpdateDuration, .5f,
		                                       true);
	}
	else
	{
		SetVisibility(ESlateVisibility::Collapsed);
		GetWorld()->GetTimerManager().ClearTimer(DurationUpdateTimer);
	}
}

void UDurationGEWidget::UpdateDuration()
{
	if (CachedOwnerASC)
	{
		TArray<TPair<float, float>> DurationInfo;
		DurationInfo = CachedOwnerASC->GetActiveEffectsTimeRemainingAndDuration(
			FGameplayEffectQuery::MakeQuery_MatchAllOwningTags(
				FGameplayTagContainer(DurationTag)));
		TPair<float, float> FoundDurationInfo;
		if (DurationInfo.Num() > 0)
		{
			FoundDurationInfo = DurationInfo[0];
		}
		if (FoundDurationInfo.Value > 0)
		{
			float ElapsedTime = FoundDurationInfo.Value - FoundDurationInfo.Key;
			float Duration = FoundDurationInfo.Value;
			EffectIcon->SetEffectImageCooldownMaterialGaugeStat(ElapsedTime / Duration);
		}
	}
}
