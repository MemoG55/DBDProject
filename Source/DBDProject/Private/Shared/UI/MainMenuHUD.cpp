// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/UI/MainMenuHUD.h"

#include "Components/WrapBox.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDStruct.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/UI/MainMenuSurvivorItemSlot.h"

void UMainMenuHUD::NativePreConstruct()
{
	Super::NativePreConstruct();
	
}

void UMainMenuHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (!SurvivorItemDatas)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("MainMenuHUD : 생존자 아이템 테이블 등록이 안되어 있습니다."));
		return;
	}

	if (!MainMenuSurvivorItemSlotClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Can't find MainMenuHUDClass"));
		return;
	}
	
	TArray<FName> RowNames;
	UDataTableFunctionLibrary::GetDataTableRowNames(SurvivorItemDatas, RowNames);
	for (FName RowName : RowNames)
	{
		UMainMenuSurvivorItemSlot* MainMenuSurvivorItemSlot = CreateWidget<UMainMenuSurvivorItemSlot>(GetOwningPlayer(), MainMenuSurvivorItemSlotClass);
		
		const FItemData* SurvivorItemData = SurvivorItemDatas->FindRow<FItemData>(RowName, TEXT("MainMenuHUD : LoadDataFromTable"));

		ItemWrapBox->AddChild(MainMenuSurvivorItemSlot);
		
		MainMenuSurvivorItemSlot->SetTextBlock_Text(SurvivorItemData->DisplayName);


		//슬릇에 데이터 전송
		MainMenuSurvivorItemSlot->SetSurvivorItem(RowName);
	}
}

void UMainMenuHUD::SetSurvivorItem_Implementation(FName SurvivorItem)
{
	ADBDPlayerState* DBDPlayerState = Cast<ADBDPlayerState>(GetOwningPlayerState());
	if (!DBDPlayerState)
	{
		//Debug::Print(TEXT("MainMenuHUD : DBDPlayerState 캐스트 실패!"), -1,  FColor::Red);
		return;
	}
	DBDPlayerState->SurvivorLoadout.ItemInfo.Item = SurvivorItem;
}
