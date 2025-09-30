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

	virtual void Init() override;

	virtual void BeginPlay() override;

	virtual void StartInteraction(AActor* Actor) override;
	virtual void FinishInteraction(AActor* Actor) override;

	virtual void UnSetInteractorLocation(AActor* Actor) override;

	virtual void OnCompleted_Implementation() override;
	virtual void OnDestroyed_Implementation() override;

	// 공통으로 적용되는 상호작용 Block 태그들
	UPROPERTY(EditAnywhere, Category = "BlockInteractTags")
	FGameplayTagContainer ActivationBlockTags;

	// 살인마에게만 적용되는 상호작용 Block 태그들
	UPROPERTY(EditAnywhere, Category = "BlockInteractTags")
	FGameplayTagContainer KillerActivationBlockTags;

	// 생존자에게만 적용되는 상호작용 Block 태그들
	UPROPERTY(EditAnywhere, Category = "BlockInteractTags")
	FGameplayTagContainer SurvivorActivationBlockTags;

public:
	virtual bool CanInteraction(AActor* Actor) override;
	virtual void SetInteractorLocation(AActor* Actor) override;

	UFUNCTION(BlueprintCallable)
	void SkillCheckResultReceivedEvent(const FGameplayEventData& Data);
};
