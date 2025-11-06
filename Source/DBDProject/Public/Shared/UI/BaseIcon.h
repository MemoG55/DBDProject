// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseIcon.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UBaseIcon : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* IconLevelImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* IconImage;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* EffectImage;
	
#pragma region EffectMaterial
	//BP에서 할당한 메테리얼
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMaterialInstance> EffectCircleCooldownMaterialInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMaterialInstance> EffectDisableMaterialInstance;

	
	//적용한 메테리얼
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterialInstanceDynamic> EffectMaterialDynamic;
#pragma endregion EffectMaterial
	
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	virtual void SetIcon(TSoftObjectPtr<UTexture2D> InputTexture2D);
	
	virtual void SetIconVisible(ESlateVisibility IsVisible);

	UFUNCTION()
	void SetIconState(EIconEffect IconEffect);

	UFUNCTION()
	void SetEffectImageCooldownMaterialGaugeStat(float inputNum);
};
