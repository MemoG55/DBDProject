// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/Component/InteractableComponent.h"
#include "ICObject.generated.h"

enum class ESkillCheckResult : uint8;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UICObject : public UInteractableComponent
{
	GENERATED_BODY()
public:
	UICObject();
protected:
	UPROPERTY()
	ADBDObject* OwningObject;
	
	UPROPERTY()
	UObjAbilitySystemComponent* OwningObjectASC;

	UPROPERTY()
	FActiveGameplayEffectHandle OwningGameplayEffectCDO;

	UPROPERTY(Replicated)
	TObjectPtr<AActor> CapturedActor;
	
public:

	UFUNCTION()
	AActor* GetCapturedActor() const;
	
	// true = 상호작용 중인 액터가 없을 때 IsActive태그가 여전히 붙어있음, false = 상호작용 중인 액터가 없을 때 IsActive태그가 제거됨
	UPROPERTY(EditAnywhere, Category = "InteractionCondition")
	bool bIsActiveWhenInteractorsEmpty = true;

protected:
	virtual void Init() override;

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void SetInteractors(AActor* Actor) override;
	virtual void UnSetInteractors(AActor* Actor) override;

#pragma region InteractCondition:
	// 공통으로 적용되는 상호작용 Block 태그
	UPROPERTY(EditAnywhere, Category = "InteractCondition")
	FGameplayTagContainer ActivationBlockTags;

	// 살인마에게만 적용되는 상호작용 Block 태그
	UPROPERTY(EditAnywhere, Category = "InteractCondition")
	FGameplayTagContainer KillerActivationBlockTags;

	// 생존자에게만 적용되는 상호작용 Block 태그
	UPROPERTY(EditAnywhere, Category = "InteractCondition")
	FGameplayTagContainer SurvivorActivationBlockTags;

	// 공통으로 적용되는 상호작용 Required 태그
	UPROPERTY(EditAnywhere, Category = "InteractCondition")
	FGameplayTagContainer ActivationRequiredTags;

	// 살인마에게만 적용되는 상호작용 Required 태그
	UPROPERTY(EditAnywhere, Category = "InteractCondition")
	FGameplayTagContainer KillerActivationRequiredTags;

	// 생존자에게만 적용되는 상호작용 Required 태그
	UPROPERTY(EditAnywhere, Category = "InteractCondition")
	FGameplayTagContainer SurvivorActivationRequiredTags;

	// 생존자만 상호작용 가능한지?
	UPROPERTY(EditAnywhere, Category = "InteractCondition")
	bool bIsSurvivorOnly = false;

	// 살인마만 상호작용 가능한지?
	UPROPERTY(EditAnywhere, Category = "InteractCondition")
	bool bIsKillerOnly = false;

	// 생존자의 위치가 지정되어있는지? (부착인지 아닌지)
	UPROPERTY(EditAnywhere, Category = "InteractCondition")
	bool bIsInteractorLocationSet = false;
#pragma endregion

#pragma region InteractionFunctions:
public:
	virtual void StartInteraction(AActor* Actor) override;
	virtual void FinishInteraction(AActor* Actor) override;
	virtual void CompleteInteraction(AActor* Actor) override;
	virtual void DestroyInteraction(AActor* Actor) override;
#pragma endregion
	
public:
	virtual bool CanInteraction(AActor* Actor) override;
	virtual void SetInteractorLocation(AActor* Actor) override;
	virtual void UnSetInteractorLocation(AActor* Actor) override;




	UFUNCTION(BlueprintCallable)
	void SkillCheckResultReceivedEvent(FGameplayEventData Data);
};
