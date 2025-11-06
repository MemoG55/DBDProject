// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PerkUIHUD.generated.h"

struct FPerkData;
class UBasePerkIcon;
class UPerkInstance;
enum class EPlayerRole : uint8;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UPerkUIHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UBasePerkIcon* PerkIcon1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UBasePerkIcon* PerkIcon2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UBasePerkIcon* PerkIcon3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UBasePerkIcon* PerkIcon4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UBasePerkIcon*> PerkIcons;

	//EffectMaterialInstances
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EffectMaterialInstance")
	UMaterialInstance* CoolDownMaterialInstance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EffectMaterialInstance")
	UMaterialInstance* DisableMaterialInstance;

	UFUNCTION(BlueprintCallable)
	void SetPerksToHUD(int index, FPerkData PerkStruct);

	virtual void NativeConstruct() override;
};
