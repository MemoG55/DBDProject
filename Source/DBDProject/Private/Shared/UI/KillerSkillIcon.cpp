// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/KillerSkillIcon.h"

#include "KMJ/AbilitySystem/HuntressAttributeSet.h"
#include "KMJ/Character/KillerHuntress.h"
#include "Components/TextBlock.h"
#include "Shared/GameFramework/DBDPlayerState.h"

void UKillerSkillIcon::OnAxeNumberChanged(float NewAxeNumber)
{
	if (CurrentAxeNum)
		CurrentAxeNum->SetText(FText::AsNumber(NewAxeNumber));
}

void UKillerSkillIcon::NativeConstruct()
{
	Super::NativeConstruct();
	Huntress =  Cast<AKillerHuntress>(GetOwningPlayerPawn());
	// JMS: UI수정: Owner에서 정보 추출
	SetKillerSkillIcon(Huntress);
}

void UKillerSkillIcon::SetKillerSkillIcon(AKillerHuntress* Character)
{
	Huntress = Character;
	if (Huntress && Huntress->HuntressAttributeSet)
	{
		Huntress->HuntressAttributeSet->OnAxeNumberChanged.RemoveDynamic(this, &UKillerSkillIcon::OnAxeNumberChanged);
		Huntress->HuntressAttributeSet->OnAxeNumberChanged.AddDynamic(this, &UKillerSkillIcon::OnAxeNumberChanged);

		if (CurrentAxeNum)
			CurrentAxeNum->SetText(FText::AsNumber(Huntress->HuntressAttributeSet->GetAxeNumber()));
	}

	SetVisibility(ESlateVisibility::Visible);
}

