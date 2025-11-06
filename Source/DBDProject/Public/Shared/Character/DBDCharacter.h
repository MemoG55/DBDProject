// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Shared/Interface/DBDWidgetInterface.h"
#include "Shared/Interface/Interactable.h"
#include "Shared/Interface/Interactor.h"
#include "DBDCharacter.generated.h"

class UDBDMotionWarpingComponent;
class UDBDHUD;
class UDBDWidgetComponent;
class UInputMappingContext;
class IInteractable;
class UPerkComponent;
enum class EPlayerRole : uint8;


// DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPerkUIInitialize, ADBDCharacter*, DBDCharacter, EPlayerRole, PlayerRole)
// ;
//
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemUIInitialize, ADBDCharacter*, DBDCharacter, EPlayerRole, PlayerRole)
// ;


UCLASS()
class DBDPROJECT_API ADBDCharacter : public ACharacter, public IAbilitySystemInterface, public IInteractable,
                                     public IInteractor, public IDBDWidgetInterface
{
	GENERATED_BODY()

public:
	ADBDCharacter();
	ADBDCharacter(const FObjectInitializer& ObjectInitializer);
	// IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// JMS : MotionWarpingComponent
	UDBDMotionWarpingComponent* GetDBDMotionWarpingComponent() const;

	// JMS : IInteractable
	UFUNCTION(BlueprintCallable, Category = "DBDCharacter")
	virtual UInteractableComponent* GetInteractableComponent() const override;
	virtual const TArray<FMotionWarpingInfo> GetMotionWarpingTargets_Implementation() override;
	// JMS : IInteractor
	virtual UInteractorComponent* GetInteractorComponent() const override;
	virtual EPlayerRole GetInteractorRole() const override;

	// JMS: UI수정: WidgetInterface
	virtual UDBDWidgetComponent* GetWidgetComponent() const override;
	
	// Server Only
	virtual void PossessedBy(AController* NewController) override;
	// Client Only
	virtual void OnRep_PlayerState() override;

	void InitializePerks(const UDataTable& DataTable, FName Perk1Name, FName Perk2Name, FName Perk3Name,
	                     FName Perk4Name);
	virtual void ServerSideInit();
	virtual void ClientSideInit();

	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	TSubclassOf<class UDBDHUD_EndGame> HUD_EndGameClass;
	UPROPERTY(VisibleAnywhere, Category = "HUD")
	class UDBDHUD_EndGame* HUD_EndGame;
	
	UPROPERTY(BlueprintReadWrite, Category = "Sound")
	UAudioComponent* PlayingAudioComponent;

#pragma region AuraSystem:
	// JMS: �라 �성�� �해 CustomDepth �더링을 �성�야 메시�을 �식 �래�에�택
	// EX) GetMesh()->SetRenderCustomDepth(false);
	virtual void EnableAura(int32 StencilValue);
	virtual void DisableAura();

	UPROPERTY(ReplicatedUsing = OnRep_AuraStencilMap)
	TArray<FStencilMap> StencilMaps;

	UFUNCTION()
	void OnRep_AuraStencilMap();

	UFUNCTION()
	virtual void SetCustomDepth(int32 value);


#pragma endregion:

	// MMJ : 캐릭터 입력 가능하게 만드는 함수
	void EnableInputGame();

	//1014_KMJ: for UI
	TArray<UPerkComponent*> GetAllPerks();

	//1014_KMJ: UIComponent
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	UDBDWidgetComponent* UIWidgetComponent;
	//PlayerHUD
	// JMS: UI수정: WidgetComponent가 관리
	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	// UDBDHUD* PlayerHUD;

	// JMS: UI수정: WidgetComponent가 델리게이트 담당
	// FOnPerkUIInitialize OnPerkUIInitialize;
	// FOnItemUIInitialize OnItemUIInitialize;

#pragma region MotionSync
public:
	//JMS : Montage Sync
	UFUNCTION(BlueprintCallable, Category = "DBDCharacter")
	float PlaySyncMontageFromServer(UAnimMontage* Montage, float PlayRate = 1.0f, FName StartSectionName = NAME_None);
	UFUNCTION(BlueprintCallable, Category = "DBDCharacter")
	float SyncTransformAndPlayMontageFromServer(FTransform ServerCharacterTransform, UAnimMontage* Montage, float PlayRate = 1.0f, FName StartSectionName = NAME_None);
	UFUNCTION(BlueprintCallable, Category = "DBDCharacter")
	void StopSyncMontageFromServer(UAnimMontage* Montage);
	UFUNCTION(BlueprintCallable, Category = "DBDCharacter")
	void LookAtTargetActorFromServer(AActor* TargetActor, float YawOffset = 0.f);
	UFUNCTION(BlueprintCallable, Category = "DBDCharacter")
	void LookAtTargetActorLocal(AActor* TargetActor, float YawOffset = 0.f);
	UFUNCTION(BlueprintCallable, Category = "DBDCharacter")
	float PlaySyncMontageFromOwnerClient(UAnimMontage* Montage, float PlayRate = 1.0f, FName StartSectionName = NAME_None);
	UFUNCTION(Client, Unreliable)
	void Client_SyncTransformByServer(FTransform ServerCharacterTransform);
private:
	UFUNCTION(Server, Reliable)
	void Server_PlaySyncMontage(UAnimMontage* Montage, float PlayRate = 1.0f, FName StartSectionName = NAME_None);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PlaySyncMontage(UAnimMontage* Montage, float PlayRate = 1.0f, FName StartSectionName = NAME_None);
	UFUNCTION(Client, Reliable)
	void Client_PlaySyncMontage(UAnimMontage* Montage, float PlayRate = 1.0f, FName StartSectionName = NAME_None);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_StopSyncMontage(UAnimMontage* Montage);
	UFUNCTION(Client, Reliable)
	void Client_StopSyncMontage(UAnimMontage* Montage);
	UFUNCTION(Client, Unreliable)
	void Client_SyncTransformAndMontage(FTransform ServerSideTransform, UAnimMontage* Montage, float PlayRate = 1.0f,
	                                    FName StartSectionName = NAME_None);
	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_SyncTransformAndMontage(FTransform ServerSideTransform, UAnimMontage* Montage, float PlayRate = 1.0f,
	                                       FName StartSectionName = NAME_None);
private:
	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_SetSurvivorRotation(FRotator TargetRotation);
	UFUNCTION(Client, Unreliable)
	void Client_SetSurvivorRotation(FRotator TargetRotation);
#pragma endregion 
protected:
	// JMS : MotionWarpingComponent
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	UDBDMotionWarpingComponent* DBDMotionWarpingComponent;
	UPROPERTY(EditAnywhere, Category = "MotionWarping")
	TArray<FMotionWarpingInfo> CharacterMotionWarpingTargetInfos;

	// JMS : InteractorComponent
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	UInteractorComponent* InteractorComponent;
	virtual void BeginPlay() override;
	void InitPerkOnClient();
	void EnableScratchMarkToCurrentClientSurvivor();

	UPROPERTY(VisibleAnywhere, Category = "Perk", Replicated)
	UPerkComponent* Perk1;
	UPROPERTY(VisibleAnywhere, Category = "Perk", Replicated)
	UPerkComponent* Perk2;
	UPROPERTY(VisibleAnywhere, Category = "Perk", Replicated)
	UPerkComponent* Perk3;
	UPROPERTY(VisibleAnywhere, Category = "Perk", Replicated)
	UPerkComponent* Perk4;
	// JMS: AuthInitPerks - �버초기 �서맞게 �식 �래�에�출 �요
	void AuthInitPerks();

	UFUNCTION(Client, Reliable)
	void Client_UpdatePerk(UPerkComponent* NewPerk1, UPerkComponent* NewPerk2, UPerkComponent* NewPerk3,
	                       UPerkComponent* NewPerk4);

#pragma region MotionWarping

public:
	UFUNCTION(BlueprintCallable, Category = "MotionWarping")
	void UpdateWarpResultOnServer();

	UFUNCTION(BlueprintCallable, Category = "DBDCharacter")
	void SyncLocationAndRotation();

protected:
	UFUNCTION(Server, Unreliable)
	void Server_UpdateLocationAndRotation(FVector NewLocation, FRotator NewRotation);
	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_UpdateLocationAndRotation(FVector NewLocation, FRotator NewRotation);
#pragma endregion

protected:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
