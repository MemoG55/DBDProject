// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Shared/Interface/Interactable.h"
#include "DBDObject.generated.h"

DECLARE_DELEGATE_OneParam(FOnObjectInteract, AActor*)
DECLARE_DELEGATE(FOnObjectComplete)
DECLARE_DELEGATE_OneParam(FOnObjectDisconnect, AActor*)

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
	FOnObjectInteract OnInteract;
	// 상호작용 완료 시 실행될 델리게이트 (발전기 수리 완료 or 이외의 모든 상호작용이 완료되었을 경우)
	FOnObjectComplete OnComplete;
	// 인터랙트 중지 시 실행될 델리게이트
	FOnObjectDisconnect OnDisconnect;

	// 정보시스템컴포넌트 (오라, 시각+청각 알림)
	
	// AbilitySystem
	UPROPERTY(VisibleDefaultsOnly)
	class UObjAbilitySystemComponent* ObjAbilitySystemComponent;

	UPROPERTY()
	class UObjAttributeSet* ObjAttributeSet;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void Init();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> TestAbility;

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

	// 상호작용 완료했을 때
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void EndInteraction(AActor* Actor);

	// 상호작용이 취소되었을때
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void CancelInteraction(AActor* Actor);

	// 상호작용 가능한 상태인지
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual bool CanInteraction(AActor* Actor);

	// 현재 상호작용중인 액터들을 반환
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual TArray<AActor*> GetInteractors();

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
	TArray<TWeakObjectPtr<AActor>> InteractedActors;
	
	// 현재 상호작용 중인 액터 저장(단일 상호작용)
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	TWeakObjectPtr<AActor> CachedInteractor;

	// 발전기같은 여러명이 상호작용할 수 있는 오브젝트에서 사용
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	TArray<TWeakObjectPtr<AActor>> CurrentCachedInteractors;

	UPROPERTY(ReplicatedUsing = OnRep_IsActive)
	bool bIsActive;

	UFUNCTION()
	void OnRep_IsActive();
	
#pragma region Animation
	// 실행할 몽타주 모음
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<FSlotAnimData> AnimData;
#pragma endregion
public:
	
	UFUNCTION(Server, Reliable)
	void Server_AddTagToObject(FGameplayTag Tag);
};


