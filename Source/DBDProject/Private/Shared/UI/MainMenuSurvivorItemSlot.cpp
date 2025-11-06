// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/MainMenuSurvivorItemSlot.h"

#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/PanelWidget.h"
#include "Shared/UI/MainMenuHUD.h"
#include "Shared/DBDDebugHelper.h"

void UMainMenuSurvivorItemSlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	SizeBox->bIsVariable = false;
	SizeBox->SetWidthOverride(200.0f);
	SizeBox->SetHeightOverride(50.0f);

	Button->bIsVariable = true;
	
	TextBlock->bIsVariable = true;

	//바인딩 때문에 호출 순서가 늦어도 BP에서 새로운 값으로 적용 안됨
	TextBlock->SetText(FText::FromString("Text Block"));
}

void UMainMenuSurvivorItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	//Button->OnClicked.AddDynamic(this, &ThisClass::Button_Click);
	
}

void UMainMenuSurvivorItemSlot::SetSurvivorItem(FName NewSurvivorItem)
{
	SurvivorItem = NewSurvivorItem;
}

void UMainMenuSurvivorItemSlot::SetTextBlock_Text(FText Text) const
{
	TextBlock->SetText(Text);
}

void UMainMenuSurvivorItemSlot::Button_Click()
{
	// UMainMenuHUD* MainMenuHUD = Cast<UMainMenuHUD>(GetParent());
	// if (!MainMenuHUD)
	// {
	// 	//Debug::Print(TEXT("MainMenuSurvivorItemSlot : MainMenuHUD 캐스트 실패"), -1, FColor::Red);
	// 	return;
	// }
	//
	// MainMenuHUD->SetSurvivorItem_Implementation(SurvivorItem);
}