// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Shared/Character/DBDCharacter.h"
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
class DBDPROJECT_API AKillerCharacter : public ADBDCharacter
{
	GENERATED_BODY()
public:
	AKillerCharacter();
	
	// IInteractable
	virtual UInteractableComponent* GetInteractableComponent() const override;

	// IInteractor
	virtual EPlayerRole GetInteractorRole() const override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void ServerSideInit() override;
	virtual void ClientSideInit() override;
protected:
	UPROPERTY(VisibleDefaultsOnly, Category="GAS")
	class UKillerAbilitySystemComponent* KillerAbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="View")
	class USpringArmComponent* CameraArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="View")
	class UCameraComponent* FollowCam;
	
	UPROPERTY(EditDefaultsOnly, Category="DataControl", meta=(AllowPrivateAccess="true"))
	UDA_KillerInput* InputData;
	
	UPROPERTY(VisibleDefaultsOnly, Category="InteractableComponent")
	UKillerInteractableComponent* KillerInteractableComponent;
	

	//살인마 시점의 살인마 애니메이션
	UPROPERTY(EditDefaultsOnly, Category="Killer_AnimBP")
	TSubclassOf<UAnimInstance> FPVAnimClass;

	//생존자가 시점의 살인마 애니메이션
	UPROPERTY(EditDefaultsOnly, Category="Killer_AnimBP")
	TSubclassOf<UAnimInstance> TPVAnimClass;
		
	//들고 있는 생존자가 있는지
	UPROPERTY(ReplicatedUsing=OnRep_CarriedSurvivorCharacter)
	ASurvivorCharacter* CarriedSurvivorCharacter = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
	UStaticMeshComponent* RightWeapon;

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
	void InitItemHUD();
	//virtual void AddControllerPitchInput(float Val) override;

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

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_KillerAimHorizontal)
	float KillerAim_Horizontal;
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_KillerAimHorizontal();
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetKillerAimHorizontal(float NewPitch);
	
	UPROPERTY(BlueprintReadWrite, Replicated)
	bool IsCarrying;
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetKiller_IsCarrying(bool bIsCarrying);

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

	//YHG : HookAura
private:
	void OnAura_Hook(FGameplayTag Tag, int32 NewCount) const;
};