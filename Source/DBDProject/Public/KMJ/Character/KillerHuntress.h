// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KMJ/Character/KillerCharacter.h"
#include "KillerHuntress.generated.h"

struct FInputActionValue;
class UHuntressAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityGrantedDelegate);

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
	virtual void ServerSideInit() override;
	virtual void ClientSideInit() override;

	// 어빌리티 부여 후 호출될 델리게이트 함수
	UFUNCTION()
	void OnAbilityGranted();
	// 델리게이트 변수
	FOnAbilityGrantedDelegate OnAbilityGrantedDelegate;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem", meta = (AllowPrivateAccess = "true"))
	UHuntressAttributeSet* HuntressAttributeSet;
};
