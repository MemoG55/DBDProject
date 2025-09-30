// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/Interface/Interactable.h"
#include "Shared/Interface/Interactor.h"
#include "KillerCharacter.generated.h"

class UKillerInteractableComponent;
class ASurvivorCharacter;
class UHuntressAttributeSet;
enum class EKillerAbilityInputID : uint8;
class UDA_KillerInput;
struct FInputActionValue;
class UKillerAttributeSet;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API AKillerCharacter : public ADBDCharacter, public IInteractable, public IInteractor
{
	GENERATED_BODY()
public:
	AKillerCharacter();
	
	// IInteractable
	UFUNCTION(BlueprintCallable, Category = "KillerCharacter")
	virtual UInteractableComponent* GetInteractableComponent() const override;
	// IInteractor
	UFUNCTION(BlueprintCallable, Category = "KillerCharacter")
	virtual UInteractorComponent* GetInteractorComponent() const override;
	UFUNCTION(BlueprintCallable, Category = "KillerCharacter")
	virtual EPlayerRole GetInteractorRole() const override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void ServerSideInit() override;
	virtual void ClientSideInit() override;
protected:
	UPROPERTY(VisibleDefaultsOnly, Category="GAS")
	class UKillerAbilitySystemComponent* KillerAbilitySystemComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="View")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="View")
	class UCameraComponent* FollowCam;
	
	UPROPERTY(EditDefaultsOnly, Category="DataControl", meta=(AllowPrivateAccess="true"))
	UDA_KillerInput* InputData;
	
	UPROPERTY(VisibleDefaultsOnly, Category="InteractableComponent")
	UKillerInteractableComponent* KillerInteractableComponent;
	
	UPROPERTY(VisibleDefaultsOnly, Category="InteractorComponent")
	UInteractorComponent* InteractorComponent;

	//살인마 시점의 살인마 애니메이션
	UPROPERTY(EditDefaultsOnly, Category="Killer_AnimBP")
	TSubclassOf<UAnimInstance> FPVAnimClass;

	//생존자가 시점의 살인마 애니메이션
	UPROPERTY(EditDefaultsOnly, Category="Killer_AnimBP")
	TSubclassOf<UAnimInstance> TPVAnimClass;
		
	//들고 있는 생존자가 있는지
	UPROPERTY(ReplicatedUsing=OnRep_CarriedSurvivorCharacter)
	ASurvivorCharacter* CarriedSurvivorCharacter = nullptr;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem", meta = (AllowPrivateAccess = "true"))
	UKillerAttributeSet* KillerAttributeSet;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	bool IsLocallyControlledByPlayer() const;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PawnClientRestart() override;

	UFUNCTION(BlueprintCallable, Category="Killer")
	ASurvivorCharacter* GetCarriedSurvivorCharacter(){return CarriedSurvivorCharacter;};

	UFUNCTION(BlueprintCallable, Category="Killer")
	void SetCarriedSurvivorCharacter(ASurvivorCharacter* Survivor){ CarriedSurvivorCharacter = Survivor; };

	UFUNCTION(BlueprintCallable, Category="Killer")
	void ClearCarriedSurvivorCharacter(){CarriedSurvivorCharacter = nullptr;};

	UFUNCTION(BlueprintCallable, Category="Killer")
	bool IsCarriedSurvivorExist(){return CarriedSurvivorCharacter != nullptr;};

	UFUNCTION()
	void OnRep_CarriedSurvivorCharacter();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetCarriedSurvivorCharacter(ASurvivorCharacter* NewSurvivorCharacter);
	
	void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
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