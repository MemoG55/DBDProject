// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "KMJ/AbilitySystem/KillerAttributeSet.h"
#include "DBDPlayerState.generated.h"

class UDBDAbilitySystemComponent;
UENUM(BlueprintType)
enum class EPlayerRole : uint8
{
	Survivor	UMETA(DisplayName = "Survivor"),
	Killer		UMETA(DisplayName = "Killer"),
};

USTRUCT(BlueprintType)
struct FSurvivorLoadout
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName Character;
	FName Item;
	FName Addon1;
	FName Addon2;
	FName Perk1;
	FName Perk2;
	FName Perk3;
	FName Perk4;
	FName Offering;
};

USTRUCT(BlueprintType)
struct FKillerLoadout
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName Character;
	FName Addon1;
	FName Addon2;
	FName Perk1;
	FName Perk2;
	FName Perk3;
	FName Perk4;
	FName Offering;
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
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_PlayerRole, Category = "PlayerRole")
	EPlayerRole PlayerRole;

	TObjectPtr<UDBDAbilitySystemComponent> DBDAbilitySystemComponent;
public:
	// IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UFUNCTION(BlueprintCallable, Category = "PlayerRole")

	EPlayerRole GetPlayerRole() const;
	UFUNCTION(BlueprintCallable, Category = "PlayerRole")
	EPlayerRole SetPlayerRole(EPlayerRole NewRole);

	void AuthInitAttributeSet();
	void AuthInitPerks();

protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere,ReplicatedUsing=OnRep_SurvivorLoadout, Category = "Loadout")
	FSurvivorLoadout SurvivorLoadout;
	UPROPERTY(EditAnywhere,ReplicatedUsing=OnRep_KillerLoadout, Category = "Loadout")
	FKillerLoadout KillerLoadout;
private:
	UFUNCTION()
	void OnRep_SurvivorLoadout();
	UFUNCTION()
	void OnRep_KillerLoadout();
	UFUNCTION()
	void OnRep_PlayerRole();
protected:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
