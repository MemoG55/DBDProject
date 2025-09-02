// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "DBDPlayerState.generated.h"

class UDBDAbilitySystemComponent;
UENUM(BlueprintType)
enum class EPlayerRole : uint8
{
	Survivor	UMETA(DisplayName = "Survivor"),
	Killer		UMETA(DisplayName = "Killer"),
};
/**
 * 
 */
UCLASS()
class DBDPROJECT_API ADBDPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
private:
	ADBDPlayerState();
	UPROPERTY(VisibleAnywhere, Category = "PlayerRole")
	EPlayerRole PlayerRole;

	TObjectPtr<UDBDAbilitySystemComponent> DBDAbilitySystemComponent;
public:
	// IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UFUNCTION(BlueprintCallable, Category = "PlayerRole")
	EPlayerRole GetPlayerRole() const;
	UFUNCTION(BlueprintCallable, Category = "PlayerRole")
	EPlayerRole SetPlayerRole(EPlayerRole NewRole);
};
