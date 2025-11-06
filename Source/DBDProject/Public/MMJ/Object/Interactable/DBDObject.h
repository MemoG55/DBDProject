// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "Shared/DBDStruct.h"
#include "Shared/Interface/Interactable.h"
#include "DBDObject.generated.h"

class UObjAbilitySystemComponent;
class UObjAttributeSet;
class UWidgetComponent;
class UICObject;


UCLASS()
class DBDPROJECT_API ADBDObject : public AActor, public IInteractable, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ADBDObject(const FObjectInitializer& ObjectInitializer);

	static FName InteractableComponentName;

	// 정보시스템컴포넌트 (오라, 시각+청각 알림)
	
	// AbilitySystem
	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UObjAbilitySystemComponent> ObjAbilitySystemComponent;

	UPROPERTY()
	UObjAttributeSet* ObjAttributeSet;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UICObject> InteractableComponent;

	UFUNCTION(BlueprintCallable)
	virtual UInteractableComponent* GetInteractableComponent() const override;
	
	void Init();

#pragma region AuraSystem:

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AuraSystem")
	TObjectPtr<UStaticMeshComponent> AuraMesh;
public:
	UPROPERTY(ReplicatedUsing = OnRep_AuraStencilMap)
	TArray<FStencilMap> StencilMaps;

	UFUNCTION()
	void OnRep_AuraStencilMap();
		
	void EnableAura();
	void EnableBackground();
	void DisableAura();
	void DisableBackground();
	UFUNCTION()
	void SetCustomDepth(int32 value);
#pragma endregion

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,  Category = "Object")
	USkeletalMeshComponent* ObjectMesh;

public:
	template < typename T >
	T* GetSkeletalMeshComponent() const
	{
		return Cast<T>(ObjectMesh);
	}

	UFUNCTION()
	USkeletalMeshComponent* GetSkeletalMeshComponent() const
	{
		return Cast<USkeletalMeshComponent>(ObjectMesh);
	}
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 결합 형태의 오브젝트인 경우 사용
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CombinedActor")
	TObjectPtr<AActor> CombinedActor;

	// 결합 형태의 오브젝트인 경우 소환할 액터의 클래스를 지정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CombinedActor")
	TSubclassOf<AActor> CombinedActorClass;

	// 엔티티가 결합되어있는 경우의 엔티티 저장 변수
	UPROPERTY()
	TObjectPtr<class AObj_Entity> Entity;

public:	
	UFUNCTION()
	AObj_Entity* GetEntity() const;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "UI")
	UWidgetComponent* WidgetComponent;

	// 방해공작이 들어왔을 때 메쉬 변화가 있어야 할 경우 이 변수를 활용해서 Visibility를 OnRep함수 안에서 구현
	UPROPERTY(ReplicatedUsing = OnRep_IsDestroyed)
	bool bIsDestroyed;

public:
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void SetDestroyed();

protected:
	// 클라이언트 쪽 액터의 Visibility 혹은 애니메이션을 처리, TODO :: 이펙트는 GameplayCue를 활용해보도록 하자
	UFUNCTION()
	virtual void OnRep_IsDestroyed();

#pragma region Animation
	// 모션워핑에 필요한 타겟, 본 등 데이터구조체
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<FMotionWarpingInfo> ObjectMotionWarpingTargetInfos;

public:
	// JMS: IInteractable을 구현한 것으로 수정
	virtual const TArray<FMotionWarpingInfo> GetMotionWarpingTargets_Implementation() override;
#pragma endregion
public:
	
};




