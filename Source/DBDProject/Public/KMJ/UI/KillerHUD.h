// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/UI/DBDHUD.h"
#include "KillerHUD.generated.h"

class UKillerSkillHUD;
class UKillerSkillIcon;
class UBaseSquareIcon;
struct FGameplayTag;
class AKillerHuntress;
class UTextBlock;
enum class EPlayerRole : uint8;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UKillerHUD : public UDBDHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "KillerHUD", meta = (BindWidget))
	UKillerSkillHUD* KillerSkillHUD;

	//IsCarring UI
	UPROPERTY(BlueprintReadWrite, Category = "KillerHUD", meta = (BindWidget))
	UBaseSquareIcon* CarriedSurvivorIcon;
	UPROPERTY(BlueprintReadWrite, Category = "KillerHUD", meta = (BindWidget))
	UKillerSkillHUD* CarryingKillerSkillHUD;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "KillerHUD")
	UDataTable* AddonTable;
	
	UFUNCTION()
	void SetCarryingUI();
	UFUNCTION()
	void SetOffCarryingKillerUI();
	// JMS: UI수정: 미사용
	// UFUNCTION()
	// virtual void SetItemHUD(ADBDCharacter* Character) override;
	UFUNCTION()
	void OnCarryingTagChanged(FGameplayTag GameplayTag, int i);
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnWalkingSpeedChanged(float NewWalkingSpeed);
	void SetKillerSkillIcon();
	// JMS: UI수정: 미사용
	// virtual void SetAddons(ADBDCharacter* Character) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	AKillerHuntress* Huntress = nullptr;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> WalkingSpeed;
	
};
