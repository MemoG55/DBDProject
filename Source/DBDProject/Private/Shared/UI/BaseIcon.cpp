// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/BaseIcon.h"

#include "Components/Image.h"
#include "Shared/DBDEnum.h"


void UBaseIcon::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseIcon::SetIcon(TSoftObjectPtr<UTexture2D> InputTexture2D)
{
	IconImage->SetBrushFromSoftTexture(InputTexture2D);
}

void UBaseIcon::SetIconVisible(ESlateVisibility IsVisible)
{
	//this->SetVisibility(IsVisible);
	BackgroundImage->SetVisibility(IsVisible);
	IconImage->SetVisibility(IsVisible);
	IconLevelImage->SetVisibility(IsVisible);
	EffectImage->SetVisibility(IsVisible);
}

void UBaseIcon::SetIconState(EIconEffect IconEffect)
{
	if (IconEffect != EIconEffect::None)
	{
		EffectImage->SetVisibility(ESlateVisibility::Visible);
		if (EffectImage && EffectDisableMaterialInstance)
		{
			// 동적 머티리얼 생성
			EffectMaterialDynamic = IconEffect == EIconEffect::Cooldown ? UMaterialInstanceDynamic::Create(EffectCircleCooldownMaterialInstance, this)
																		: UMaterialInstanceDynamic::Create(EffectDisableMaterialInstance, this);
			// UI 이미지에 적용
			EffectImage->SetBrushFromMaterial(EffectMaterialDynamic);
		}
	}
	else
	{
		if (EffectImage)
		{
			EffectImage->SetBrushFromMaterial(nullptr);
		}
		// 이미지 숨기기
		EffectImage->SetVisibility(ESlateVisibility::Hidden);
		// 포인터 정리
		EffectMaterialDynamic = nullptr;
	}
}

void UBaseIcon::SetEffectImageCooldownMaterialGaugeStat(float inputNum)
{
	if (EffectMaterialDynamic)
	{
		EffectMaterialDynamic->SetScalarParameterValue(FName("CoolDownRemainingPercent"), inputNum);
	}
}
