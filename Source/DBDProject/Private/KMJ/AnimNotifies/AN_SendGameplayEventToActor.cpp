// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/AnimNotifies/AN_SendGameplayEventToActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsManager.h"
#include "Components/BoxComponent.h"
#include "Engine/OverlapResult.h"
#include "JMS/Character/SurvivorCharacter.h"
#include "KMJ/AbilitySystem/KillerAttributeSet.h"
#include "KMJ/Character/KillerHuntress.h"
#include "MMJ/Object/Interactable/DBDObject.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDDebugHelper.h"

void UAN_SendGameplayEventToActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                          const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	// MeshComp가 유효한지 확인
	if (!MeshComp || !MeshComp->GetOwner())
		return;

	// RightAxe의 Collision 체크
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(MeshComp->GetOwner());  // 자기 자신 제외

	// RightAxe의 위치 및 크기 설정
	FVector RightAxeLocation = FVector::ZeroVector;
	FVector RightAxeExtent = FVector::ZeroVector;
	UStaticMeshComponent* RightAxeComponent = nullptr;
	TArray<UStaticMeshComponent*> StaticMeshComponents;
	MeshComp->GetOwner()->GetComponents<UStaticMeshComponent>(StaticMeshComponents);

	for (UStaticMeshComponent* Component : StaticMeshComponents)
	{
		if (Component && Component->GetName() == TEXT("RightWeapon"))
		{
			RightAxeComponent = Component;
			break;
		}
	}

	if (RightAxeComponent)
	{
		// RightAxe의 Box Collision Component 찾기
		UBoxComponent* RightAxeBoxCollision = RightAxeComponent->GetOwner()->FindComponentByClass<UBoxComponent>();
    
		if (RightAxeBoxCollision)
		{
			// Box Collision의 위치 가져오기
			RightAxeLocation = RightAxeBoxCollision->GetComponentLocation();

			// Box Collision의 크기 (Extent)를 가져옴
			RightAxeExtent = RightAxeBoxCollision->GetScaledBoxExtent();
		}
		else
		{
			// Box Collision이 없다면 StaticMeshComponent의 위치를 가져옴
			RightAxeLocation = RightAxeComponent->GetComponentLocation();
		}
	}

	//NextSection 초기화
	NextSectionName = TEXT("Miss");

	// Overlap 체크 (Box 형태로)
	bool bHit = MeshComp->GetWorld()->OverlapMultiByChannel(OverlapResults, RightAxeLocation, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeBox(RightAxeExtent), CollisionParams);
	
	for (const FOverlapResult& Result : OverlapResults)
	{
		if (AActor* OverlappedActor = Result.GetActor())
		{
			//Debug::Print(FString::Printf(TEXT("Overlapped Actor: %s"), *OverlappedActor->GetName()), 330);
			
			
			if (OverlappedActor == Cast<AKillerCharacter>(MeshComp->GetOwner())->GetCarriedSurvivorCharacter())
				continue;

			FGameplayTag Survivor_Status_Dying = FGameplayTag::RequestGameplayTag(FName("Survivor.Status.Dying"));
			if (OverlappedActor->IsA(ASurvivorCharacter::StaticClass()))
			{
				if (UDBDBlueprintFunctionLibrary::NativeActorHasTag(OverlappedActor, Survivor_Status_Dying))
				{
					//Debug::Print(FString::Printf(TEXT("Overlapped Actor Has Dying Tag: %s"), *OverlappedActor->GetName()), 328);
					continue;
				}
			}

			if (OverlappedActor != Cast<AKillerCharacter>(MeshComp->GetOwner())->GetCarriedSurvivorCharacter())
			{
				//Debug::Print(FString::Printf(TEXT("First Overlapped Actor: %s"), *OverlappedActor->GetName()), 329);
				NextSectionName = GetNextMontageSectionBasedOnActor(OverlappedActor);
				RightAxeComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				break;
			}
		}
	}
	PlayNextMontageSection(MeshComp, NextSectionName);
}

FString UAN_SendGameplayEventToActor::GetNextMontageSectionBasedOnActor(AActor* OverlappedActor)
{
	if (OverlappedActor->IsA(ASurvivorCharacter::StaticClass()))
	{
		Cast<ASurvivorCharacter>(OverlappedActor)->AttackSurvivor();
		return TEXT("Survivor"); 
	}
	else if (OverlappedActor->IsA(ADBDObject::StaticClass()))
	{
		return TEXT("Object");
	}
	return TEXT("Miss");
}

void UAN_SendGameplayEventToActor::PlayNextMontageSection(USkeletalMeshComponent* MeshComp, const FString& SectionName)
{
	if (!MeshComp || !MeshComp->GetOwner())
		return;

	// 현재 재생 중인 몽타주가 있으면 해당 섹션을 변경
	UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
	AKillerHuntress* Huntress = Cast<AKillerHuntress>(MeshComp->GetOwner());
	float playAnimRate = 1.0f;
	if (Huntress)
	{
		playAnimRate = Huntress->KillerAttributeSet->AfterAttackRate.GetCurrentValue();
	}
	if (AnimInstance)
	{
		UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();
		if (CurrentMontage)
		{
			// 섹션 변경
			if (SectionName == TEXT("Survivor"))
			{
				AnimInstance->Montage_JumpToSection(TEXT("Survivor"), CurrentMontage);
			}
			else if (SectionName == TEXT("Object"))
			{
				AnimInstance->Montage_JumpToSection(TEXT("Object"), CurrentMontage);
			}
			else
			{
				AnimInstance->Montage_JumpToSection(TEXT("Miss"), CurrentMontage);
			}

			// 재생 속도 설정 (예: 1.5배로 빠르게 재생)
			AnimInstance->Montage_SetPlayRate(CurrentMontage, playAnimRate);
		}
	}
}



