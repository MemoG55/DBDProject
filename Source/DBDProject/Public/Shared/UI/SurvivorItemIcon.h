// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/UI/BaseSquareIcon.h"
#include "SurvivorItemIcon.generated.h"

class UDBDDataBase;
class ASurvivorItem;
struct FItemData;
class ASurvivorCharacter;
struct FOnAttributeChangeData;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API USurvivorItemIcon : public UBaseSquareIcon
{
	GENERATED_BODY()

public:
	//아이템 내구도 이미지 ) 모양
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UImage> ItemGaugeImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UImage> ItemControlIconImage;
	
	//적용할 메테리얼
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMaterialInstance> TopDownItemGaugeMaterialInstance;
	
	// 동적 머티리얼 인스턴스 저장용
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> ItemGaugeMaterialInstanceDynamic;

	// JMS: GAS에 있는 델리게이트 사용하려고 시그니쳐 변경
	//)모양 아이템 내구도 이미지 게이지 수치 설정
	void SetItemGaugeImageMaterialGaugeStat(const FOnAttributeChangeData& OnAttributeChangeData);
	
	virtual void NativeConstruct() override;

	void InitializeWithItemData(const FItemData& ItemData);
	UFUNCTION()
	void OnEquippedItemChanged(ASurvivorItem* NewItem);
private:
	UPROPERTY()
	ASurvivorCharacter* OwnerSurvivor;
	UPROPERTY()
	UDBDDataBase* CachedDBDDataBase;
};
