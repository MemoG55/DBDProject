// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/GeneratorIcon.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/UI/DBDWidgetComponent.h"


void UGeneratorIcon::SetGeneratorImage(int32 LeftGenerator)
{
    if (LeftGenerator == 0)
    {
        if (IsValid(IconImage))
        {
            IconImage->SetVisibility(ESlateVisibility::Hidden);
        }
        if (IsValid(LeftDoorText))
        {
            LeftDoorText->SetVisibility(ESlateVisibility::Hidden);
        }
        if (IsValid(ExitDoorIcon))
        {
            ExitDoorIcon->SetVisibility(ESlateVisibility::Visible);
        }
    }
    else
    {
        if (IsValid(IconImage))
        {
            IconImage->SetVisibility(ESlateVisibility::Visible);
        }
        if (IsValid(LeftDoorText))
        {
            LeftDoorText->SetText(FText::AsNumber(LeftGenerator));
            LeftDoorText->SetVisibility(ESlateVisibility::Visible);
        }
        if (IsValid(ExitDoorIcon))
        {
            ExitDoorIcon->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}

void UGeneratorIcon::NativeConstruct()
{
    Super::NativeConstruct();
    // JMS: UI수정: 위젯 컴포넌트를 통해 업데이트
    ADBDCharacter* OwningPlayerPawn = Cast<ADBDCharacter>(GetOwningPlayerPawn());
    if (OwningPlayerPawn)
    {
        OwningPlayerPawn->GetWidgetComponent()->OnUpdateGeneratorCount.AddDynamic(this, &UGeneratorIcon::SetGeneratorImage);
    }
}
