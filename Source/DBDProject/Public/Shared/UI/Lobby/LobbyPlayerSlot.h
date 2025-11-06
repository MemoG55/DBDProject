// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyPlayerSlot.generated.h"

enum class EPlayerRole : uint8;
class ADBDPlayerState;
class UImage;
class UComboBoxString;
class UTextBlock;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API ULobbyPlayerSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY()
	ADBDPlayerState* OldPS;
	UFUNCTION()
	void BindingGameState();
	
	UFUNCTION()
	void BindingPlayerState(ADBDPlayerState* PS);

	UFUNCTION()
	void BindingPlayerController();

	UFUNCTION()
	void BindingSelf();
	
	UFUNCTION()
	void OnCharacterLoaded();

	UFUNCTION()
	void InitCharacterMeshSelect();

	UFUNCTION()
	void HandleOwning();

	UFUNCTION()
	void HandleByOther();
private:
	UPROPERTY(EditDefaultsOnly, Category = "TextBox", meta = (BindWidget))
	TObjectPtr<UTextBlock> TBPlayerRole;

	UPROPERTY(EditDefaultsOnly, Category = "TextBox", meta = (BindWidget))
	TObjectPtr<UTextBlock> TBPlayerName;

	UPROPERTY(EditDefaultsOnly, Category = "TextBox", meta = (BindWidget))
	TObjectPtr<UComboBoxString> CBMeshSelect;

	UPROPERTY(EditDefaultsOnly, Category = "TextBox", meta = (BindWidget))
	TObjectPtr<UImage> MeshImage;
	
	UPROPERTY(EditDefaultsOnly, Category = "PlayerSlotData")
	TObjectPtr<UTexture2D> MeshNoneImage;

	UPROPERTY(EditDefaultsOnly, Category = "PlayerSlotData")
	TObjectPtr<UTexture2D> MeshKillerImage;
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> PlayerImage;

	UPROPERTY(EditAnywhere, Category = "PlayerSlotData")
	TObjectPtr<UTexture2D> SurvivorImage;

	UPROPERTY(EditAnywhere, Category = "PlayerSlotData")
	TObjectPtr<UTexture2D> KillerImage;

	UPROPERTY(EditAnywhere, Category = "PlayerSlotData")
	TObjectPtr<UTexture2D> ReadyImage;

	UPROPERTY()
	TObjectPtr<UDataTable> CharacterDB;
public:
	UFUNCTION()
	void HandleMeshSelection(ESlateVisibility bVisiblity);
	
	UFUNCTION()
	void SetPlayerSlot(ADBDPlayerState* PS = nullptr);

	UFUNCTION()
	void SetPlayerRole(const EPlayerRole& PlayerRole);

	UFUNCTION()
	void SetPlayerName(const FString& PlayerName);

	UFUNCTION()
	void SetPlayerMesh(const FString& PlayerMesh);

private:
	UFUNCTION()
	void OnChangedMeshSelection(FString SelectedItem, ESelectInfo::Type SelectInfo);
};
