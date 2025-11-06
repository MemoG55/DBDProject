// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_SendGameplayEventToActor.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UAN_SendGameplayEventToActor : public UAnimNotify
{
	GENERATED_BODY()

private:
	FString NextSectionName = TEXT("Miss");

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	// 새로운 함수: 액터에 맞는 섹션 이름을 결정하는 함수
	FString GetNextMontageSectionBasedOnActor(AActor* OverlappedActor);

	// 새로운 함수: 몽타주 섹션을 전환하는 함수
	void PlayNextMontageSection(USkeletalMeshComponent* MeshComp, const FString& SectionName);
};