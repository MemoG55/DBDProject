// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/Character/DBDCharacter.h"
#include "SurvivorCharacter.generated.h"

struct FGameplayTag;
enum class ESurvivorAbilityInputID : uint8;
class UDA_SurvivorInput;
struct FInputActionValue;
class UAnimInstance;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API ASurvivorCharacter : public ADBDCharacter
{
	GENERATED_BODY()
public:
	ASurvivorCharacter();
private:
	UPROPERTY(VisibleDefaultsOnly, Category="View")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleDefaultsOnly, Category="View")
	class UCameraComponent* FollowCam;
	
	UPROPERTY(EditDefaultsOnly, Category="DataControl", meta=(AllowPrivateAccess="true"))
	UDA_SurvivorInput* InputData;
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PawnClientRestart() override;
private:
	void AbilityInput(const FInputActionValue& InputActionValue, ESurvivorAbilityInputID InputID);
	
	void LookAction(const FInputActionValue& InputActionValue);
	void MoveAction(const FInputActionValue& InputActionValue);

	FVector GetLookRightDirection() const;
	FVector GetLookForwardDirection() const;
	FVector GetMoveForwardDirection() const;
public:
	virtual void PossessedBy(AController* NewController) override;


	UFUNCTION(BlueprintCallable)
	void AddUniqueTag(FGameplayTag Tag);
	
	UFUNCTION(Server, Reliable)
	void ServerAddUniqueTag(const FGameplayTag& Tag);

	UFUNCTION(BlueprintCallable)
	void RemoveTag(FGameplayTag Tag);

	UFUNCTION(Server, Reliable)
	void ServerRemoveTag(const FGameplayTag& Tag);

	UFUNCTION(BlueprintCallable)
	void PrintHasTag(FGameplayTag Tag);

	UFUNCTION(Server, Reliable)
	void ServerPrintHasTag(const FGameplayTag& Tag);

	UFUNCTION(BlueprintCallable)
	void SendGameplayTagEvent(FGameplayTag Tag);

	UFUNCTION(Server, Reliable)
	void ServerSendGameplayTagEvent(const FGameplayTag& Tag);
};