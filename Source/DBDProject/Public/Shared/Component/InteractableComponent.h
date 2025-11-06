// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Components/BoxComponent.h"
#include "Shared/DBDGameplayTags.h"
#include "MMJ/Object/Interactable/DBDObject.h"
#include "MMJ/Object/GAS/ObjAbilitySystemComponent.h"
#include "InteractableComponent.generated.h"


enum class EPlayerRole : uint8;

UENUM(BlueprintType)
enum class EInteractableCollisionType : uint8
{
	Box,
	Sphere,
	Capsule,
};

// 상호작용 시작 시(액터인자)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectInteractWithActor, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectInteractSourceObject, AActor*, Object);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnObjectInteractInfo, AActor*, SourceObject, AActor*, InteractActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectInteract);
// 상호작용 중단 시(액터인자=저장된액터제거)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectDisconnectWithActor, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectDisconnectSourceObject, AActor*, Object);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnObjectDisconnectInfo, AActor*, SourceObject, AActor*, InteractActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectDisconnect);
// 상호작용 완료 시(액터인자= 추후 퀘스트나 오라시스템에 사용가능해보임)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectCompleteWithActor, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectCompleteSourceObject, AActor*, Object);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnObjectCompleteInfo, AActor*, SourceObject, AActor*, InteractActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectComplete);
// 손상 적용 시
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectDestroyWithActor, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectDestroySourceObject, AActor*, Object);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnObjectDestroyInfo, AActor*, SourceObject, AActor*, InteractActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectDestroy);

/**
 * 전체적인 Flow
 * InteractorActor -> InteractWithActor(델리게이트) BroadCast -> 바인딩된 InteractedWithActor(Actor) 안에서 StartInteraction() 함수 실행
 * -> 태그부여 및 Location 등, 전처리 후 Interact(델리게이트) BroadCast
 * InteractorActor -> DisconnectWithActor(델리게이트) BroadCast -> 바인딩된 DisconnetedWithActor(Actor) 안에서 EndInteraction() 함수 실행
 * -> 태그삭제 및 전처리 후 Disconnect(델리게이트) BoradCast
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DBDPROJECT_API UInteractableComponent : public UBoxComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableComponent();

protected:
	UFUNCTION()
	virtual void Init();


public:
	UFUNCTION()
	bool CheckAuthority() const;
	
#pragma region Delegate:
	// 인터랙트 시작 시 실행될 델리게이트 (추후 정보 시스템에 연결될 수 있으므로 액터 인자 추가)
	UPROPERTY(BlueprintAssignable)
	FOnObjectInteractWithActor OnInteractWithActor;
	
	UPROPERTY(BlueprintAssignable)
	FOnObjectInteractSourceObject OnInteractSourceObject;

	UPROPERTY(BlueprintAssignable)
	FOnObjectInteractInfo OnInteractInfo;
	
	UPROPERTY(BlueprintAssignable)
	FOnObjectInteract OnInteract;

	// 인터랙트 중지 시 실행될 델리게이트
	UPROPERTY(BlueprintAssignable)
	FOnObjectDisconnectWithActor OnDisconnectWithActor;
	
	UPROPERTY(BlueprintAssignable)
	FOnObjectDisconnectSourceObject OnDisconnectSourceObject;

	UPROPERTY(BlueprintAssignable)
	FOnObjectDisconnectInfo OnDisconnectInfo;
	
	UPROPERTY(BlueprintAssignable)
	FOnObjectDisconnect OnDisconnect;
	
	// 상호작용 완료 시 실행될 델리게이트 (발전기 수리 완료 or 이외의 모든 상호작용이 완료되었을 경우)
	UPROPERTY(BlueprintAssignable)
	FOnObjectCompleteWithActor OnCompleteWithActor;
	
	UPROPERTY(BlueprintAssignable)
	FOnObjectCompleteSourceObject OnCompleteSourceObject;

	UPROPERTY(BlueprintAssignable)
	FOnObjectCompleteInfo OnCompleteInfo;
	
	UPROPERTY(BlueprintAssignable)
	FOnObjectComplete OnComplete;
	
	// 손상 시
	UPROPERTY(BlueprintAssignable)
	FOnObjectDestroyWithActor OnDestroyWithActor;
	
	UPROPERTY(BlueprintAssignable)
	FOnObjectDestroySourceObject OnDestroySourceObject;

	UPROPERTY(BlueprintAssignable)
	FOnObjectDestroyInfo OnDestroyInfo;
	
	UPROPERTY(BlueprintAssignable)
	FOnObjectDestroy OnDestroy;
#pragma endregion 

protected:
	UFUNCTION()
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InteractableTag;
protected:
	
#pragma region Owner:
	UPROPERTY()
	AActor* OwningActor;
	
	UPROPERTY()
	UDBDAbilitySystemComponent* OwningASC;
#pragma endregion

	// Called when the game starts
	virtual void BeginPlay() override;

#pragma region InteractionVariablesGetterSetter:
protected:
	UPROPERTY(EditDefaultsOnly, Category = "InteractionVariables")
	FGameplayAttribute TaskAttribute;

	// 상호작용 중인 액터들 배열
	UPROPERTY(VisibleDefaultsOnly, Category = "InteractionVariables")
	TArray<AActor*> InteractedActors;
	
public:
	// 마지막으로 등록된 상호작용액터
	UPROPERTY(BlueprintReadOnly, Category = "InteractionVariables")
	TObjectPtr<AActor> CachedCurrentInteractor;
	
public:
	// 현재 오브젝트에 상호작용이 가능한 총 인원
	UPROPERTY(EditDefaultsOnly, Category = "InteractionVariables")
	int32 MaxInteractorCount;
	
	// 상호작용할 액터가 위치해야할 곳을 맵으로 저장
	UPROPERTY(EditDefaultsOnly, Category = "InteractionVariables")
	TMap<FGameplayTag, FName> ActorAttachSocketName;
	
	// 현재 상호작용중인 액터들의 상호작용속도 반환
	UFUNCTION(BlueprintCallable, Category = "InteractionVariablesSetter")
	virtual float GetTaskAttributeOfInteractors() const;

	// 현재 상호작용 진행도 반환
	UFUNCTION(BlueprintCallable, Category = "InteractionVariablesSetter")
	virtual float GetInteractionProgress();

	// 현재 상호작용중인 액터의 상호작용 시간 반환
	UFUNCTION(BlueprintCallable, Category = "InteractionVariablesSetter")
	virtual float GetInteractionDuration(AActor* Actor);

	// 사용할 TaskAttribue 설정
	UFUNCTION(BlueprintCallable, Category = "InteractionVariablesSetter")
	void SetTaskAttribute(FGameplayAttribute GameplayAttribute);
	
	UFUNCTION(Category = "InteractionVariablesSetter")
	virtual void SetInteractorLocation(AActor* Actor);

	UFUNCTION(Category = "InteractionVariablesSetter")
	virtual void UnSetInteractorLocation(AActor* Actor);
	
	// 상호작용 가능한 상태인지
	UFUNCTION(BlueprintCallable, Category = "InteractionVariablesSetter")
	virtual bool CanInteraction(AActor* Actor);

	// 현재 상호작용중인 액터들을 반환
	UFUNCTION(BlueprintCallable, Category = "InteractionVariablesSetter")
	virtual TArray<AActor*> GetInteractors();
protected:
	// 현재 상호작용 중인 액터 저장
	UFUNCTION(BlueprintCallable, Category = "InteractionVariablesSetter")
	virtual void SetInteractors(AActor* Actor);

	// 상호작용 중인 액터 제거
	UFUNCTION(BlueprintCallable, Category = "InteractionVariablesSetter")
	virtual void UnSetInteractors(AActor* Actor);
#pragma endregion
	
#pragma region InteractionFunctions:
public:
	UFUNCTION(BlueprintCallable)
	void BeginInteraction(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void EndInteraction(AActor* Actor);
	
	// 상호작용 시작했을 때
	UFUNCTION(BlueprintCallable, Category = "InteractionFunctions")
	virtual void StartInteraction(AActor* Actor);

	// 상호작용 끝났을 때
	UFUNCTION(BlueprintCallable, Category = "InteractionFunctions")
	virtual void FinishInteraction(AActor* Actor);


	// 상호작용 완료되었을 때
	UFUNCTION(BlueprintCallable, Category = "InteractionFunctions")
	virtual void CompleteInteraction(AActor* Actor);
	
	// 손상을 가하는 상호작용이 행해졌을때
	UFUNCTION(BlueprintCallable, Category = "InteractionFunctions")
	virtual void DestroyInteraction(AActor* Actor);

	// 상호작용 중 일어나는 실시간 틱
	UFUNCTION(BlueprintCallable, Category = "InteractionFunctions")
	virtual void TickInteraction(AActor* Actor);
#pragma endregion	

#pragma region InteractionDelegateBindFunctions:
protected:
	// 델리게이트에 의해 발동되는 함수(이펙트 같은것만 쓰도록 하기)
	UFUNCTION(Server, Unreliable)
	virtual void OnInteracted();

	UFUNCTION(Server, Unreliable)
	virtual void OnInteractedWithActor(AActor* Actor);

	UFUNCTION(Server, Unreliable)
	virtual void OnDisconnected();

	UFUNCTION(Server, Unreliable)
	virtual void OnDisconnectedWithActor(AActor* Actor);

	UFUNCTION(Server, Unreliable)
	virtual void OnCompleted();

	UFUNCTION(Server, Unreliable)
	virtual void OnCompletedWithActor(AActor* Actor);

	UFUNCTION(Server, Unreliable)
	virtual void OnDestroyed();

	UFUNCTION(Server, Unreliable)
	virtual void OnDestroyedWithActor(AActor* Actor);
#pragma endregion

public:
#pragma region StatusGetter:
	// IsActive?
	UFUNCTION(BlueprintPure)
	bool IsActivate();

	// IsComplete?
	UFUNCTION(BlueprintPure)
	bool IsComplete();

	// IsDestroy?
	UFUNCTION(BlueprintPure)
	bool IsDestroy();
#pragma endregion
};
