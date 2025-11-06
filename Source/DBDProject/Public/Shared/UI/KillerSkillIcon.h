// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/UI/BaseSquareIcon.h"
#include "KillerSkillIcon.generated.h"

class AKillerHuntress;
class UTextBlock;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UKillerSkillIcon : public UBaseSquareIcon
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void OnAxeNumberChanged(float NewAxeNumber);

	virtual void NativeConstruct() override;

	//도끼 개수 및 이동속도 갱신
	UFUNCTION()
	void SetKillerSkillIcon(AKillerHuntress* Character);

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> CurrentAxeNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UImage> ItemControlIconImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	AKillerHuntress* Huntress = nullptr;
	
};
