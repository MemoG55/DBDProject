// Fill out your copyright notice in the Description page of Project Settings.
// TODO: WidgetComponent 제거 후 HUD 클래스 만들어서 관리
// TODO: Tag, Attribute이벤트 ASC 관련 클래스로 이동
#pragma once

#include "CoreMinimal.h"
#include "Shared/DBDStruct.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/Interface/Interactable.h"
#include "Shared/Interface/Interactor.h"
#include "SurvivorCharacter.generated.h"

class AObj_Hook;
struct FOnAttributeChangeData;
class UDBDHUD;
class UWidgetComponent;
class ADBDPlayerState;
class ASurvivorItem;
class USurvivorInteractableComponent;
class UInteractorComponent;
class USkillCheckComponent;
class USurvivorAttributeSet;
class USurvivorAbilitySystemComponent;
class USpringArmComponent;
class UCameraComponent;
class UDA_SurvivorASCData;
class UInputMappingContext;
class ADBDObject;
struct FGameplayTag;
enum class ESurvivorAbilityInputID : uint8;
class UDA_SurvivorInput;
struct FInputActionValue;
class UAnimInstance;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEquippedItemChangedDelegate, ASurvivorItem*, EquippedItem);
UCLASS()
class DBDPROJECT_API ASurvivorCharacter : public ADBDCharacter, public IInteractable, public IInteractor
{
	GENERATED_BODY()

public:
	ASurvivorCharacter();

	// IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// IInteractable
	virtual UInteractableComponent* GetInteractableComponent() const;
	// IInteractor
	virtual UInteractorComponent* GetInteractorComponent() const;
	virtual EPlayerRole GetInteractorRole() const;

	USkillCheckComponent* GetSkillCheckComponent() const;

private:
	UPROPERTY(VisibleDefaultsOnly, Category="View")
	USurvivorAbilitySystemComponent* SurvivorAbilitySystemComponent;
	
	UPROPERTY()
	USurvivorAttributeSet* SurvivorAttributeSet;

	UPROPERTY(VisibleDefaultsOnly, Category="SkillCheck")
	USkillCheckComponent* SkillCheckComponent;

	UPROPERTY(VisibleDefaultsOnly, Category="InteractableComponent")
	USurvivorInteractableComponent* SurvivorInteractableComponent;
	
	UPROPERTY(VisibleDefaultsOnly, Category="InteractorComponent")
	UInteractorComponent* InteractorComponent;

	UPROPERTY(VisibleDefaultsOnly, Category="View")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleDefaultsOnly, Category="View")
	UCameraComponent* FollowCam;

	UPROPERTY(EditDefaultsOnly, Category="DataControl", meta=(AllowPrivateAccess="true"))
	UDA_SurvivorInput* InputData;

	UPROPERTY(VisibleAnywhere, Category="UI")
	UDBDHUD* TempPrototypeWidget;

	UPROPERTY(EditAnywhere, Category="Temp")
	TSubclassOf<UDBDHUD> TempPrototypeWidgetClass;
#pragma region Hook
protected:
	UPROPERTY(VisibleAnywhere, Category="Interaction")
	TObjectPtr<AObj_Hook> CurrentHook;

	void RegisterHook(AObj_Hook* Hook);
public:
	AObj_Hook* GetCurrentHook() const;
#pragma endregion
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation")
	UAnimMontage* DeathMontage;

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PawnClientRestart() override;
	virtual void Tick(float DeltaSeconds) override;
	void BindGASChangeDelegate();
// GAS - TagDelegate
#pragma region AttributeChangeEvent
protected:
	void HealProgressChanged(const FOnAttributeChangeData& OnAttributeChangeData);
	void DyingHPChanged(const FOnAttributeChangeData& OnAttributeChangeData);
#pragma endregion
#pragma region TagChangeEvent
protected:
	void DeathTagUpdate(const FGameplayTag Tag, int32 NewCount);
	void EscapeTagUpdate(const FGameplayTag Tag, int32 NewCount);
#pragma endregion
	ADBDPlayerState* GetDBDPlayerState() const;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
private:
	void AbilityInput(const FInputActionValue& InputActionValue, ESurvivorAbilityInputID InputID);

	void LookAction(const FInputActionValue& InputActionValue);
	void MoveAction(const FInputActionValue& InputActionValue);

	FVector GetLookRightDirection() const;
	FVector GetLookForwardDirection() const;
	FVector GetMoveForwardDirection() const;


public:
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
#pragma region ItemControl
public:
	// 캐릭터의 Equip, Drop에서 월드에 아이템을 배치하는 역할, 아이템 클래스에서 Owner의 태그를 업데이트하는 역할
	// 서버에서 실행
	void EquipItem(ASurvivorItem* ItemToEquip);
	// 서버에서 실행
	void DropItem();
	// 서버에서 실행
	void ExchangeItem(ASurvivorItem* ItemToExchange);
	// 서버에서 실행
	void UseEquippedItem();
	
	void UpdateCurrentItemUI();
	FEquippedItemChangedDelegate EquippedItemChangedDelegate;

	UPROPERTY(EditDefaultsOnly, Category="Item")
	FName ItemSocketName;
protected:
	UPROPERTY(VisibleDefaultsOnly, Category="Item", ReplicatedUsing=OnRep_EquippedItem)
	TObjectPtr<ASurvivorItem> EquippedItem;
	UFUNCTION()
	void OnRep_EquippedItem(ASurvivorItem* OldItem);
#pragma endregion

#pragma region Misc
public:
	// Movement Mode만 None, Walk 전환
	UFUNCTION(BlueprintCallable, Category = "SurvivorCharacterMisc")
	void MoveEnabled(bool bEnable);
	// Collision, Movement Mode, Gravity 활성/비활성 전환
	UFUNCTION(BlueprintCallable, Category = "SurvivorCharacterMisc")
	void SetCollisionAndGravityEnabled(bool bEnable);
	UFUNCTION(BlueprintPure, Category = "SurvivorCharacterMisc")
	bool IsCollisionAndGravityEnabled() const;
private:
	bool bIsCollisionAndGravityEnabled = true;
	
#pragma endregion 
#pragma region StateControl
public:
	UFUNCTION(BlueprintCallable)
	void AttackSurvivor();
	UFUNCTION(BlueprintCallable)
	void SetSurvivorInjured();
	UFUNCTION(BlueprintCallable)
	void SetSurvivorDying();
	UFUNCTION(BlueprintCallable)
	void SetSurvivorNormal();
	UFUNCTION(BlueprintCallable)
	void CaptureSurvivor();
	UFUNCTION(BlueprintCallable)
	void HookSurvivor(AObj_Hook* Hook);
	UFUNCTION(BlueprintCallable)
	void ReleaseSurvivor();
	UFUNCTION(BlueprintCallable)
	void SetSurvivorEscaped();
	UFUNCTION(BlueprintCallable)
	void SetSurvivorDead();
#pragma endregion
	
	void ServerSideInit();
	void ClientSideInit();
	bool IsLocallyControlledByPlayer() const;

protected:
	void InitializeEquippedItem(FSurvivorItemInstanceInfo InitialItemInfo);
#pragma region TagControl
protected:
	UFUNCTION(BlueprintCallable)
	void AddUniqueTag(FGameplayTag Tag);
	UFUNCTION(BlueprintCallable)
	void AddTag(FGameplayTag Tag);

	UFUNCTION(Server, Reliable)
	void ServerAddUniqueTag(const FGameplayTag& Tag);
	UFUNCTION(Server, Reliable)
	void ServerAddTag(const FGameplayTag& Tag);

	UFUNCTION(BlueprintCallable)
	void RemoveTag(FGameplayTag Tag);
	UFUNCTION(BlueprintCallable)
	void RemoveTagAll(FGameplayTag Tag);

	UFUNCTION(Server, Reliable)
	void ServerRemoveTag(const FGameplayTag& Tag);
	UFUNCTION(Server, Reliable)
	void ServerRemoveTagAll(const FGameplayTag& Tag);

	UFUNCTION(BlueprintCallable)
	void PrintHasTag(FGameplayTag Tag);

	UFUNCTION(Server, Reliable)
	void ServerPrintHasTag(const FGameplayTag& Tag);

	UFUNCTION(BlueprintCallable)
	void SendGameplayTagEvent(FGameplayTag Tag);

	UFUNCTION(Server, Reliable)
	void ServerSendGameplayTagEvent(const FGameplayTag& Tag);
#pragma endregion
};
