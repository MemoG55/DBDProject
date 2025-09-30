// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "KMJ/Character/KillerCharacter.h"
#include "KillerHuntress.generated.h"

struct FInputActionValue;
class UHuntressAttributeSet;


UCLASS()
class DBDPROJECT_API AKillerHuntress : public AKillerCharacter
{
	GENERATED_BODY()
public:
	AKillerHuntress();
	virtual void InitHuntressAttribute();
	//virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PawnClientRestart() override;
	void OnGameplayEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
	virtual void ServerSideInit() override;
	virtual void ClientSideInit() override;
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem", meta = (AllowPrivateAccess = "true"))
	UHuntressAttributeSet* HuntressAttributeSet;

	// Bind With GA Event
	//void OnKillerSkillPressed();

	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* IA_Killer_Skill;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* IA_Killer_Attack;
	*/
protected:
	UPROPERTY(ReplicatedUsing=OnRep_WalkSpeedChanged)
	float ReplicatedWalkSpeed;

	UFUNCTION()
	void OnRep_WalkSpeedChanged();

	UFUNCTION(BlueprintCallable)
	void OnWalkingSpeedChanged(float NewWalkingSpeed);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
