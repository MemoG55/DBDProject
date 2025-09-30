// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "DBDCharacter.generated.h"

class UInputMappingContext;
class IInteractable;
class UPerkInstance;

UCLASS()
class DBDPROJECT_API ADBDCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ADBDCharacter();
	// IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Server Only
	virtual void PossessedBy(AController* NewController) override;
	// Client Only
	virtual void OnRep_PlayerState() override;

	void InitializePerks(const UDataTable& DataTable, FName Perk1Name, FName Perk2Name, FName Perk3Name, FName Perk4Name);
	virtual void ServerSideInit();
	virtual void ClientSideInit();
	
	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	TSubclassOf<class UDBDHUD_EndGame> HUD_EndGameClass;
	UPROPERTY(VisibleAnywhere, Category = "HUD")
	class UDBDHUD_EndGame* HUD_EndGame;
protected:

	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Perk1, Category = "Perk")
	UPerkInstance* Perk1;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Perk2, Category = "Perk")
	UPerkInstance* Perk2;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Perk3, Category = "Perk")
	UPerkInstance* Perk3;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Perk4, Category = "Perk")
	UPerkInstance* Perk4;

	void AuthInitPerks();
private:
	UFUNCTION()
	void OnRep_Perk1();
	UFUNCTION()
	void OnRep_Perk2();
	UFUNCTION()
	void OnRep_Perk3();
	UFUNCTION()
	void OnRep_Perk4();
protected:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
};
