// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "KMJ/Character/KillerCharacter.h"
#include "KillerHuntress.generated.h"

class UAxeComponent;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAxeComponent* AxeComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem", meta = (AllowPrivateAccess = "true"))
	UHuntressAttributeSet* HuntressAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	UStaticMeshComponent* LeftAxe;

protected:
	UPROPERTY(ReplicatedUsing=OnRep_WalkSpeedChanged)
	float ReplicatedWalkSpeed;

	UFUNCTION()
	void OnRep_WalkSpeedChanged();

public:
	UFUNCTION(BlueprintCallable)
	void OnWalkingSpeedChanged(float NewWalkingSpeed);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SetLeftAxeVisibility(bool bVisible);
	
};
