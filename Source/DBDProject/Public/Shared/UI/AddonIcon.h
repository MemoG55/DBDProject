// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/UI/BaseSquareIcon.h"
#include "AddonIcon.generated.h"

class UDBDDataBase;
class ASurvivorItem;
struct FItemAddonData;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UAddonIcon : public UBaseSquareIcon
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> AddonCrossImage;

	UFUNCTION()
	void SetAddOnImage(FItemAddonData AddonData);

	UFUNCTION()
	void ClearAddonImage();

protected:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnEquippedItemChanged(ASurvivorItem* NewItem);
	UPROPERTY()
	UDBDDataBase* CachedDBDDataBase;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AddonIndex = 0;
};
