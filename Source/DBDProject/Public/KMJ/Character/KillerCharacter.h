// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/Character/DBDCharacter.h"
#include "KillerCharacter.generated.h"

class UHuntressAttributeSet;
enum class EKillerAbilityInputID : uint8;
class UDA_KillerInput;
struct FInputActionValue;
class UKillerAttributeSet;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API AKillerCharacter : public ADBDCharacter
{
	GENERATED_BODY()
public:
	AKillerCharacter();

	//virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void ServerSideInit();
	virtual void ClientSideInit();
private:
	//UPROPERTY(VisibleDefaultsOnly, Category="GAS")
	//class UKillerAbilitySystemComponent* KillerAbilitySystemComponent;
	
protected:
	UPROPERTY(VisibleDefaultsOnly, Category="View")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleDefaultsOnly, Category="View")
	class UCameraComponent* FollowCam;
	
	UPROPERTY(EditDefaultsOnly, Category="Killer", meta=(AllowPrivateAccess = "true"))
	class UStaticMeshComponent* HeadMesh;

	UPROPERTY(EditDefaultsOnly, Category="DataControl", meta=(AllowPrivateAccess="true"))
	UDA_KillerInput* InputData;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem", meta = (AllowPrivateAccess = "true"))
	//UKillerAttributeSet* KillerAttributeSet;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "StartupData")
	//TSoftObjectPtr<UDataAsset_Startup> StartupData;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PawnClientRestart() override;
	
	virtual void InitKillerAttribute();
	
private:
	void AbilityInput(const FInputActionValue& InputActionValue, EKillerAbilityInputID InputID);
	void LookAction(const FInputActionValue& InputActionValue);
	void MoveAction(const FInputActionValue& InputActionValue);

	FVector GetLookRightDirection() const;
	FVector GetLookForwardDirection() const;
	FVector GetMoveForwardDirection() const;

protected:
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsGrounded;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsFalling;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsIdle;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsLeftMoving;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "StateControl")
	bool bIsRightMoving;

public:
	UFUNCTION()
	bool GetIsGrounded() const;
	UFUNCTION()
	bool GetIsFalling() const;
	UFUNCTION()
	bool GetIsIdle() const;
	UFUNCTION()
	bool GetIsRightMoving() const;
	UFUNCTION()
	bool GetIsLeftMoving() const;

};