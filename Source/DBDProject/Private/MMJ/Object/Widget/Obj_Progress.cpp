// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Widget/Obj_Progress.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "MMJ/Object/GAS/ObjAttributeSet.h"
#include "Shared/GAS/DBDAbilitySystemComponent.h"

void UObj_Progress::SetObjectASC(UDBDAbilitySystemComponent* ASC, const FGameplayAttribute& CurrentAttribute,
                                 const FGameplayAttribute& MaxAttribute)
{

	if (OwnerASC)
	{
		bool bFound = false;
		float RecoverValue = OwnerASC->GetGameplayAttributeValue(UObjAttributeSet::GetRecoverTaskAttribute(), bFound);
		if (bFound)
		{
			OwnerASC->GetGameplayAttributeValueChangeDelegate(UObjAttributeSet::GetRecoverTaskAttribute()).RemoveAll(this);
		}
	}
	if (IsValid(ASC))
	{
		bool bFound = false;
		float RecoverValue = ASC->GetGameplayAttributeValue(UObjAttributeSet::GetRecoverTaskAttribute(), bFound);
		if (bFound)
		{
			CachedRecoverValue = RecoverValue;
			ASC->GetGameplayAttributeValueChangeDelegate(UObjAttributeSet::GetRecoverTaskAttribute()).AddUObject(this, &ThisClass::UpdateRecoverValue);
		}
	}
	Super::SetObjectASC(ASC, CurrentAttribute, MaxAttribute);

	if (IsValid(RecoverProgressMarking))
	{
		RecoverProgressMarking->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UObj_Progress::NativeConstruct()
{
	Super::NativeConstruct();
}

void UObj_Progress::Update()
{
	Super::Update();

	if (IsValid(RecoverProgressMarking))
	{
		if (CachedRecoverValue > 0)
		{
			if (UCanvasPanelSlot* MarkerSlot = Cast<UCanvasPanelSlot>(RecoverProgressMarking->Slot))
			{
				FGeometry BarGeometry = ProgressBar->GetCachedGeometry();
				float BarLength = BarGeometry.GetLocalSize().X;

				float MarkerWidth = MarkerSlot->GetSize().X;
				float NewPercent = CachedRecoverValue / CachedMaxValue;
				float NewXPosition = (BarLength * NewPercent) - (MarkerWidth / 2.f);

				FVector2D CurrentPosition = MarkerSlot->GetPosition();
				FVector2D NewPosition(NewXPosition, CurrentPosition.Y);

				MarkerSlot->SetPosition(NewPosition);
			}
			
			if (!RecoverProgressMarking->IsVisible())
			{
				RecoverProgressMarking->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else
		{
			if (RecoverProgressMarking->IsVisible())
			{
				RecoverProgressMarking->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
}

void UObj_Progress::UpdateRecoverValue(const FOnAttributeChangeData& ChangeData)
{
	CachedRecoverValue = ChangeData.NewValue;
}
