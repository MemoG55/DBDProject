// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DBDHUD.generated.h"

enum class EPlayerRole : uint8;
class UGeneratorIcon;
class UAbilityNameOnlyWidget;
class UAbilityProgressWidget;
class UKillerSkillHUD;
class ADBDCharacter;
class UPerkUIHUD;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEscapeTimerBeginDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEscapeTimerEndDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEscapeTimerDelegate, float, NewValue);
UCLASS()
class DBDPROJECT_API UDBDHUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// EndGameHUD
	UPROPERTY(EditAnywhere, Category = UI, meta = (BindWidget))
	TObjectPtr<class UEscapeTimerUI> EndGameHUD;
	
	// ProgressBar
	UPROPERTY(EditAnywhere, Category = UI, meta = (BindWidget))
	TObjectPtr<class UObj_Progress> ProgressHUD;
	
	//Perks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta=(BindWidget))
	UPerkUIHUD* PerkUIHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	UDataTable* PerkDataTable;

	// Survivor Ability Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta=(BindWidget))
	UAbilityProgressWidget* AbilityProgressWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta=(BindWidget))
	UAbilityNameOnlyWidget* AbilityNameOnlyWidget;

	//KMJ_1028_LeftGenerator
	UPROPERTY(EditAnywhere, Category = UI, meta=(BindWidget))
	TObjectPtr<UGeneratorIcon> LeftGeneratorIcon;

public:
	// JMS: UI수정: Owner정보를 통해 데이터 접근, InitializePerkWidget으로 변경
	// UFUNCTION(BlueprintCallable)
	// void SetPerkUIHUD(ADBDCharacter* Character, EPlayerRole PlayerRole);
	UFUNCTION(BlueprintCallable)
	void InitializePerkWidget();

	UFUNCTION(BlueprintCallable)
	void SetProgressHUD(class UDBDAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable)
	void SetEndGameHUD();

	UFUNCTION(Client, Unreliable)
	void SetLeftGeneratorIcon(int32 Left);

	UFUNCTION()
	UEscapeTimerUI* GetEndGameHUD();

	UFUNCTION()
	UGeneratorIcon* GetLeftGeneratorIcon();
	
	UFUNCTION()
	void UpdateEndGameHUD(float NewValue);
	
	virtual void NativeConstruct() override;

	virtual void SetAddons(ADBDCharacter* Character);
	
	virtual void SetItemHUD(ADBDCharacter* Character);

	void UpdateAbilityWidget(bool bIsVisible, FText Description, float Percentage);
	void UpdateAbilityNameOnlyWidget(bool bIsVisible, FText Description);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	ADBDCharacter* OwnerCharacter = nullptr;
};
