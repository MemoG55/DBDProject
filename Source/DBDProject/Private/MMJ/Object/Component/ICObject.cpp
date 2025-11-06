// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Component/ICObject.h"

#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/Character/DBDCharacter.h"

UICObject::UICObject()
{
	// 상호작용 완료된 오브젝트는 더이상 상호작용 불가능
	ActivationBlockTags.AddTag(DBDGameplayTags::Object_Status_IsComplete);
	// 상호작용 불가능 상태의 태그가 붙은 오브젝트는 상호작용 불가능
	ActivationBlockTags.AddTag(DBDGameplayTags::Object_Status_IsInActive);
}

AActor* UICObject::GetCapturedActor() const
{
	return CapturedActor;
}

void UICObject::Init()
{
	Super::Init();
}

void UICObject::BeginPlay()
{
	Super::BeginPlay();

	if (ADBDObject* Object = Cast<ADBDObject>(OwningActor))
	{
		OwningObject = Object;
		OwningObjectASC = Cast<UObjAbilitySystemComponent>(OwningASC);
	}
}

void UICObject::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UICObject, CapturedActor, COND_None, REPNOTIFY_Always);
}

void UICObject::SetInteractors(AActor* Actor)
{
	Super::SetInteractors(Actor);

	if (bIsInteractorLocationSet)
	{
		SetInteractorLocation(Actor);
	}
}

void UICObject::UnSetInteractors(AActor* Actor)
{
	Super::UnSetInteractors(Actor);

	if (bIsInteractorLocationSet)
	{
		UnSetInteractorLocation(Actor);
	}
}

void UICObject::StartInteraction(AActor* Actor)
{
	Super::StartInteraction(Actor);

	// ActivateGE를 StartInteraction에서 실행(공통)
	if (OwningObjectASC->GetObjDataAsset() && OwningObjectASC->GetObjDataAsset()->ActivateEffect)
	{
		if (!OwningGameplayEffectCDO.IsValid())
		{
			FGameplayEffectContextHandle SpecHandle = OwningObjectASC->MakeEffectContext();
			FGameplayEffectSpecHandle Spec = OwningObjectASC->MakeOutgoingSpec(
				OwningObjectASC->GetObjDataAsset()->ActivateEffect, 1, SpecHandle);
			OwningGameplayEffectCDO = OwningObjectASC->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
		}
	}

	SetInteractors(Actor);
}

void UICObject::FinishInteraction(AActor* Actor)
{
	Super::FinishInteraction(Actor);

	UnSetInteractors(Actor);
	
	if (!bIsActiveWhenInteractorsEmpty)
	{
		// ActivateGE를 StartInteraction에서 제거(공통)
		if (InteractedActors.IsEmpty() && !UDBDBlueprintFunctionLibrary::NativeActorHasTag(
			OwningObject, DBDGameplayTags::Object_Status_IsComplete))
		{
			if (OwningObjectASC->GetObjDataAsset() && OwningObjectASC->GetObjDataAsset()->ActivateEffect)
			{
				if (OwningGameplayEffectCDO.IsValid())
				{
					OwningObjectASC->RemoveActiveGameplayEffect(OwningGameplayEffectCDO);
					OwningGameplayEffectCDO.Invalidate();
				}
			}
		}
	}
}

void UICObject::CompleteInteraction(AActor* Actor)
{
	Super::CompleteInteraction(Actor);

	// ActivateGE를 제거(공통)
	if (OwningGameplayEffectCDO.IsValid())
	{
		OwningObjectASC->RemoveActiveGameplayEffect(OwningGameplayEffectCDO);
		OwningGameplayEffectCDO.Invalidate();
	}
	
	// CompleteGE를 적용(공통)
	if (OwningObjectASC->GetObjDataAsset() && OwningObjectASC->GetObjDataAsset()->CompleteEffect)
	{
		FGameplayEffectContextHandle SpecHandle = OwningObjectASC->MakeEffectContext();
		FGameplayEffectSpecHandle Spec = OwningObjectASC->MakeOutgoingSpec(
			OwningObjectASC->GetObjDataAsset()->CompleteEffect, 1, SpecHandle);
		OwningObjectASC->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
	}

	OnComplete.Broadcast();
	OnCompleteSourceObject.Broadcast(OwningObject);
	if (ADBDCharacter* Character = Cast<ADBDCharacter>(Actor))
	{
		OnCompleteInfo.Broadcast(OwningObject, Actor);
	}
}

void UICObject::UnSetInteractorLocation(AActor* Actor)
{
	Super::UnSetInteractorLocation(Actor);

	Actor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}



void UICObject::DestroyInteraction(AActor* Actor)
{
	Super::DestroyInteraction(Actor);

	// DestroyEffect를 적용 : IsDestroy태그
	if (OwningObjectASC->GetObjDataAsset()->DestroyEffect != nullptr)
	{
 		FGameplayEffectContextHandle SpecHandle = OwningObjectASC->MakeEffectContext();
		FGameplayEffectSpecHandle Spec = OwningObjectASC->MakeOutgoingSpec(
			OwningObjectASC->GetObjDataAsset()->DestroyEffect, 1, SpecHandle);
		OwningObjectASC->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
	}

	OnDestroy.Broadcast();
	OnDestroySourceObject.Broadcast(OwningObject);
	if (ADBDCharacter* Character = Cast<ADBDCharacter>(Actor))
	{
		OnDestroyInfo.Broadcast(OwningObject, Actor);
	}
}

bool UICObject::CanInteraction(AActor* Actor)
{
	if (!Super::CanInteraction(Actor))
	{
		return false;
	}
	if (OwningObjectASC->HasAnyMatchingGameplayTags(ActivationBlockTags))
	{
		return false;
	}
	if (!ActivationRequiredTags.IsEmpty() && !OwningObjectASC->HasAnyMatchingGameplayTags(ActivationRequiredTags))
	{
		return false;
	}
	if (UDBDBlueprintFunctionLibrary::IsKiller(Actor))
	{
		if (OwningObjectASC->HasAnyMatchingGameplayTags(KillerActivationBlockTags) || bIsSurvivorOnly)
		{
			return false;
		}
		if (!KillerActivationRequiredTags.IsEmpty() && !OwningObjectASC->HasAnyMatchingGameplayTags(KillerActivationRequiredTags))
		{
			return false;
		}
	}
	if (UDBDBlueprintFunctionLibrary::IsSurvivor(Actor))
	{
		if (OwningObjectASC->HasAnyMatchingGameplayTags(SurvivorActivationBlockTags) || bIsKillerOnly)
		{
			return false;
		}
		if (!SurvivorActivationRequiredTags.IsEmpty() && !OwningObjectASC->HasAnyMatchingGameplayTags(SurvivorActivationRequiredTags))
		{
			return false;
		}
	}
	return true;
}

void UICObject::SetInteractorLocation(AActor* Actor)
{
	Super::SetInteractorLocation(Actor);

	if (!ActorAttachSocketName.Contains(DBDGameplayTags::Shared_Direction_Default))
	{
		return;
	}
	if (Actor)
	{
		// 액터와의 방향계산해서 적절한 위치로 이동시킴
		FGameplayTag DirectionTag = UDBDBlueprintFunctionLibrary::ComputeInteractDirection(OwningActor, Actor);

		FName SocketName = ActorAttachSocketName[DBDGameplayTags::Shared_Direction_Default];

		if (DirectionTag.IsValid() && ActorAttachSocketName.Contains(DirectionTag))
		{
			SocketName = ActorAttachSocketName[DirectionTag];
		}
		// JMS: Actor가 DBDCharacter일 경우 캐릭터의 joint_Char소켓을 인터랙터 소켓에 붙임 
		if (ADBDCharacter* DBDCharacter = Cast<ADBDCharacter>(Actor))
		{
			UDBDBlueprintFunctionLibrary::AttachDBDCharacterToMeshSocket(OwningObject->GetSkeletalMeshComponent(),
																		 SocketName, DBDCharacter);
			return;
		}

		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Actor->GetActorLocation(), GetOwner()->GetActorLocation());
		Rotation.Pitch = 0.f;
		Actor->SetActorRotation(Rotation);
		
		FVector SocketLocation = OwningObject->GetSkeletalMeshComponent()->GetSocketLocation(SocketName);
		Actor->SetActorLocation(SocketLocation);
		
	}
}

void UICObject::SkillCheckResultReceivedEvent(FGameplayEventData Data)
{
	if (!CheckAuthority()) return;

	// if (Data.EventTag.IsValid() && Data.EventTag == DBDGameplayTags::Object_Event_Check)
	// {
	// 	// 스킬체크 대성공 보너스
	// 	if (Data.InstigatorTags.HasTag(DBDGameplayTags::Object_Event_Result_Success)
	// 		&& !OwningObjectASC->GetObjDataAsset()->SkillCheckSuccessEffects.IsEmpty())
	// 	{
	// 		for (const FObjGEStruct GE : OwningObjectASC->GetObjDataAsset()->SkillCheckSuccessEffects)
	// 		{
	// 			FGameplayEffectSpecHandle SpecHandle = OwningObjectASC->MakeOutgoingSpec(
	// 				GE.GameplayEffect, 1, OwningObjectASC->MakeEffectContext());
	// 			OwningObjectASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	// 		}
	// 	}
	// 	// 스킬체크 실패 페널티 (진행도 감소 + 알림 + 상호작용 불가)
	// 	if (Data.InstigatorTags.HasTag(DBDGameplayTags::Object_Event_Result_Failure)
	// 		&& !OwningObjectASC->GetObjDataAsset()->SkillCheckSuccessEffects.IsEmpty())
	// 	{
	// 		for (const FObjGEStruct GE : OwningObjectASC->GetObjDataAsset()->SkillCheckFailureEffects)
	// 		{
	// 			FGameplayEffectSpecHandle SpecHandle = OwningObjectASC->MakeOutgoingSpec(
	// 				GE.GameplayEffect, 1, OwningObjectASC->MakeEffectContext());
	// 			OwningObjectASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	// 		}
	// 	}
	// }
}
