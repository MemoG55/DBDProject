// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GAS/GE/ObjGameplayEffect.h"
#include "Shared/Interface/Interactable.h"
#include "DBDObject.generated.h"

// 상호작용 시작 시(액터인자)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectInteractWithActor, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectInteract);
// 상호작용 중단 시(액터인자=저장된액터제거)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectDisconnectWithActor, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectDisconnect);
// 상호작용 완료 시(액터인자= 추후 퀘스트나 오라시스템에 사용가능해보임)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectCompleteWithActor, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectComplete);


DECLARE_DELEGATE(FOnStartInteract)

USTRUCT(BlueprintType)
struct FSlotAnimData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimSequence* Sequence;
};

UCLASS()
class DBDPROJECT_API ADBDObject : public AActor, public IInteractable, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ADBDObject();

	// 인터랙트 시작 시 실행될 델리게이트 (추후 정보 시스템에 연결될 수 있으므로 액터 인자 추가)
	FOnObjectInteractWithActor OnInteractWithActor;
	FOnObjectInteract OnInteract;
	// 인터랙트 중지 시 실행될 델리게이트 
	FOnObjectDisconnectWithActor OnDisconnectWithActor;
	FOnObjectDisconnect OnDisconnect;
	// 상호작용 완료 시 실행될 델리게이트 (발전기 수리 완료 or 이외의 모든 상호작용이 완료되었을 경우)
	FOnObjectCompleteWithActor OnCompleteWithActor;
	FOnObjectComplete OnComplete;

	// 테스트용도 델리게이트
	FOnStartInteract OnStartInteract;

	// 정보시스템컴포넌트 (오라, 시각+청각 알림)
	
	// AbilitySystem
	UPROPERTY(VisibleDefaultsOnly)
	class UObjAbilitySystemComponent* ObjAbilitySystemComponent;

	UPROPERTY()
	class UObjAttributeSet* ObjAttributeSet;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void Init();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SearchNearbyActors();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> TestAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> TestEffect;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,  Category = "Object")
	USkeletalMeshComponent* ObjectMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Object")
	UBoxComponent* ObjectCollision;

	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interaction_Implementation(AActor* Actor) override;

	UFUNCTION()
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#pragma region Interaction
	// 상호작용 시작했을 때
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void StartInteraction(AActor* Actor);

	// 상호작용 중 일어나는 실시간 틱
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void TickInteraction(AActor* Actor);

	// 상호작용 끝났을 때
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void EndInteraction(AActor* Actor);

	// 상호작용 완료되었을 때
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void CompleteInteraction(AActor* Actor);

	// 상호작용이 취소되었을때
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void CancelInteraction(AActor* Actor);

	// 상호작용 가능한 상태인지
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual bool CanInteraction(AActor* Actor);

	// 현재 상호작용중인 액터들을 반환
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual TArray<AActor*> GetInteractors();

	// 현재 상호작용 중인 액터 저장
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void SetInteractors(AActor* Actor);

	// 상호작용 중인 액터 제거
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void UnSetInteractors(AActor* Actor);

	// 현재 상호작용중인 액터들의 상호작용속도 반환
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual float GetTaskSpeedOfInteractors() const { return 0.0f;};

	// 현재 상호작용 진행도 반환
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual float GetInteractionProgress();

	// 현재 상호작용중인 액터의 상호작용 시간 반환
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual float GetInteractionDuration(AActor* Actor);
	
	// 델리게이트 발동 함수
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void OnInteractionStarted();

	// 델리게이트 발동 함수
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void OnInteractionEnded();
#pragma endregion
	
protected:
	// 상호작용 중인 액터들 배열 (발전기만 쓰므로 추후 발전기쪽으로 이동해야할수도)
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	TArray<AActor*> InteractedActors;
	
	// 현재 상호작용 중인 액터 저장(단일 상호작용)
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	TWeakObjectPtr<AActor> CachedInteractor;

	// 발전기같은 여러명이 상호작용할 수 있는 오브젝트에서 사용
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	TArray<TWeakObjectPtr<AActor>> CurrentCachedInteractors;

	// 현재 오브젝트에 상호작용이 가능한 총 인원
	UPROPERTY()
	int32 MaxInteractorCount;

	// 파괴공작이 일어났을 경우
	UFUNCTION()
	virtual void OnDestroyed(FGameplayTag Tag, int32 count);

public:
#pragma region IsActive
private:
	UPROPERTY()
	bool bIsActive;
public:
	UFUNCTION(BlueprintCallable, Category = "Status")
	void SetIsActive(bool Activation);

	UFUNCTION(BlueprintPure, Category = "Status")
	bool GetIsActive();
#pragma endregion

#pragma region CanActive
private:
	UPROPERTY()
	bool bCanActive;
public:
	UFUNCTION(BlueprintCallable, Category = "Status")
	void SetCanActive(bool Activation);

	UFUNCTION(BlueprintPure, Category = "Status")
	bool GetCanActive();
#pragma endregion

#pragma region IsComplete
private:
	UPROPERTY()
	bool bIsComplete;
public:
	UFUNCTION(BlueprintCallable, Category = "Status")
	void SetIsComplete(bool bComplete);

	UFUNCTION(BlueprintPure, Category = "Status")
	bool GetIsComplete();
#pragma endregion
protected:
#pragma region Animation
	// 실행할 몽타주 모음
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<FSlotAnimData> AnimData;
#pragma endregion
public:
	
};




