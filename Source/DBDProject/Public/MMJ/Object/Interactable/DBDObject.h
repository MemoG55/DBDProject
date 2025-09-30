// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MMJ/Object/GAS/ObjAbilitySystemComponent.h"
#include "../GAS/GE/ObjGameplayEffect.h"
#include "Shared/Interface/Interactable.h"
#include "DBDObject.generated.h"

class UWidgetComponent;
class UObj_HUD;

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

class UInteractableComponent;

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
	class UObjAbilitySystemComponent* ObjAbilitySystemComponent;

	UPROPERTY()
	class UObjAttributeSet* ObjAttributeSet;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(VisibleDefaultsOnly)
	UInteractableComponent* InteractableComponent;

	UFUNCTION(BlueprintCallable)
	virtual UInteractableComponent* GetInteractableComponent() const override;
	
	void Init();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,  Category = "Object")
	USkeletalMeshComponent* ObjectMesh;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	USkeletalMeshComponent* GetSkeletalMeshComponent() const;

protected:
	// UI
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UObj_HUD> ObjHUDClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "UI")
	UWidgetComponent* WidgetComponent;
	
	UPROPERTY()
	UObj_HUD* ObjHUD;

#pragma region Animation
	// 실행할 몽타주 모음
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<FSlotAnimData> AnimData;
#pragma endregion
public:
	
};




