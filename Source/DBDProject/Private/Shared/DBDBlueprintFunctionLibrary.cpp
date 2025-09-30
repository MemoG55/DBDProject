// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/DBDBlueprintFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Camera/CameraShakeSourceActor.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Shared/DBDEnum.h"
#include "Shared/DBDGameplayTags.h"
#include "Shared/Character/DBDCharacter.h"
#include "Shared/GameFramework/DBDPlayerState.h"
#include "Shared/GAS/DBDAbilitySystemComponent.h"

UDBDAbilitySystemComponent* UDBDBlueprintFunctionLibrary::NativeGetAbilitySystemComponentFromActor(AActor* Actor)
{
	check(Actor);

	return CastChecked<UDBDAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor));
}

void UDBDBlueprintFunctionLibrary::AddUniqueTagToActor(AActor* Actor, FGameplayTag Tag)
{
	UDBDAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);

	if (!ASC->HasMatchingGameplayTag(Tag))
	{
		ASC->AddLooseGameplayTag(Tag);
		ASC->AddReplicatedLooseGameplayTag(Tag);
	}
}


void UDBDBlueprintFunctionLibrary::RemoveTagFromActor(AActor* Actor, FGameplayTag Tag)
{
	UDBDAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);


	if (ASC->HasMatchingGameplayTag(Tag))
	{
		ASC->RemoveLooseGameplayTag(Tag);
		ASC->RemoveReplicatedLooseGameplayTag(Tag);
	}
}

bool UDBDBlueprintFunctionLibrary::NativeActorHasTag(AActor* Actor, FGameplayTag Tag)
{
	UDBDAbilitySystemComponent* ASC = NativeGetAbilitySystemComponentFromActor(Actor);
	return ASC->HasMatchingGameplayTag(Tag);
}

void UDBDBlueprintFunctionLibrary::BP_HasTag(AActor* Actor, FGameplayTag Tag, EBaseConfirmType& OutType)
{
	OutType = NativeActorHasTag(Actor, Tag) ? EBaseConfirmType::Yes : EBaseConfirmType::No;
}

void UDBDBlueprintFunctionLibrary::ApplyGameplayEffectToTargetActor(AActor* TargetActor, AActor* SourceActor,
                                                                    TSubclassOf<UGameplayEffect> GameplayEffectClass,
                                                                    int level)
{
	UDBDAbilitySystemComponent* SourceASC = NativeGetAbilitySystemComponentFromActor(SourceActor);
	UDBDAbilitySystemComponent* TargetASC = NativeGetAbilitySystemComponentFromActor(TargetActor);
	UGameplayEffect* GEInstance = nullptr;

	if (GameplayEffectClass)
	{
		GEInstance = NewObject<UGameplayEffect>(TargetASC, GameplayEffectClass);
	}
	SourceASC->ApplyGameplayEffectToTarget(GEInstance, TargetASC);
	FGameplayEffectSpecHandle GESpec = UAbilitySystemBlueprintLibrary::MakeSpecHandle(
		GEInstance, SourceActor, SourceActor, level);
	SourceASC->ApplyGameplayEffectSpecToTarget(*GESpec.Data.Get(), TargetASC);
}

FGameplayTag UDBDBlueprintFunctionLibrary::ComputeInteractDirection(const AActor* Object, const AActor* Interactor)
{
	const FVector ObjectForward = Object->GetActorForwardVector();
	const FVector ObjectToInteractorNormalized = (Interactor->GetActorLocation() - Object->GetActorLocation()).
		GetSafeNormal();

	const float DotResult = FVector::DotProduct(ObjectForward, ObjectToInteractorNormalized);
	float OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(ObjectForward, ObjectToInteractorNormalized);

	//UE_LOG(LogTemp, Warning, TEXT("MMJ : ObjectLocation-> %s, InteractorLocation-> %s"), *Object->GetActorLocation().ToString(), *Interactor->GetActorLocation().ToString());

	if (CrossResult.Z < 0.f)
	{
		OutAngleDifference *= -1.f;
	}
	if (OutAngleDifference >= -65.f && OutAngleDifference <= 65.f)
	{
		return DBDGameplayTags::Shared_Direction_Front;
	}
	else if (OutAngleDifference < -65.f && OutAngleDifference >= -115.f)
	{
		return DBDGameplayTags::Shared_Direction_Left;
	}
	else if (OutAngleDifference > 65.f && OutAngleDifference <= 115.f)
	{
		return DBDGameplayTags::Shared_Direction_Right;
	}
	else if (OutAngleDifference < -115.f || OutAngleDifference > 115.f)
	{
		return DBDGameplayTags::Shared_Direction_Back;
	}
	return DBDGameplayTags::Shared_Direction_Default;
}

EPlayerRole UDBDBlueprintFunctionLibrary::GetPlayerRole(const AActor* Actor)
{
	// Actor가 �인마인지, �존�인지 �별�는 로직 �요 
	if (const ADBDCharacter* Character = Cast<ADBDCharacter>(Actor))
	{
		if (APlayerController* PC = Cast<APlayerController>(Character->GetController()))
		{
			if (ADBDPlayerState* PS = PC->GetPlayerState<ADBDPlayerState>())
			{
				return PS->GetPlayerRole();
			}
		}
	}
	return EPlayerRole();
}

bool UDBDBlueprintFunctionLibrary::IsSurvivor(const AActor* Actor)
{
	if (GetPlayerRole(Actor) == EPlayerRole::Survivor)
	{
		return true;
	}
	return false;
}

bool UDBDBlueprintFunctionLibrary::IsKiller(const AActor* Actor)
{
	if (GetPlayerRole(Actor) == EPlayerRole::Killer)
	{
		return true;
	}
	return false;
}

void UDBDBlueprintFunctionLibrary::RemoveAllSubTags(FName TagMask, UAbilitySystemComponent* TargetASC)
{
	if (!TargetASC->GetOwner()->HasAuthority())
	{
		return;
	}
	FGameplayTag RootTag = FGameplayTag::RequestGameplayTag(TagMask);
	FGameplayTagContainer TagsToRemove;

	FGameplayTagContainer CurrentTags;
	TargetASC->GetOwnedGameplayTags(CurrentTags);

	for (auto& Tag : CurrentTags)
	{
		if (Tag.MatchesTag(RootTag))
		{
			TagsToRemove.AddTag(Tag);
		}
	}

	TargetASC->RemoveLooseGameplayTags(TagsToRemove);
	TargetASC->RemoveReplicatedLooseGameplayTags(TagsToRemove);
}

void UDBDBlueprintFunctionLibrary::AttachDBDCharacterToMeshSocket(USkeletalMeshComponent* Mesh, FName MeshSocket,
                                                                  ADBDCharacter* Character,
                                                                  FName CharacterSocket)
{
	Character->K2_DetachFromActor(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld);


	if (!Character || !Mesh || !Mesh->DoesSocketExist(MeshSocket))
	{
		Debug::Print(TEXT("JMS11 : AttachDBDCharacterToSocket() : Invalid Parameter"), 11);
		return;
	}

	USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
	FVector MeshSocketLocation = Mesh->GetSocketLocation(MeshSocket);
	FVector CharacterBaseLocation = CharacterMesh->GetSocketLocation(CharacterSocket);
	FVector CharacterMeshOffset = Character->GetActorLocation() - CharacterBaseLocation;
	FVector CharacterActorLocation = Character->GetActorLocation();
	DrawDebugSphere(Character->GetWorld(), MeshSocketLocation, 10, 12, FColor::Red, true);
	DrawDebugSphere(Character->GetWorld(), CharacterBaseLocation, 10, 12, FColor::Blue, true);
	DrawDebugSphere(Character->GetWorld(), CharacterActorLocation, 10, 12, FColor::Green, true);
	DrawDebugSphere(Character->GetWorld(), MeshSocketLocation + CharacterMeshOffset, 10, 12, FColor::Yellow, true);

	FRotator MeshSocketRotation = Mesh->GetSocketRotation(MeshSocket);
	FRotator CharacterBaseRotation = CharacterMesh->GetSocketRotation(CharacterSocket);
	FRotator CharacterMeshRotation = Character->GetActorRotation() - CharacterBaseRotation;
	FRotator CharacterActorRotation = Character->GetActorRotation();

	//Debug::Print(FString::Printf(TEXT("@@@@@ MeshSocketLocation: (%f, %f, %f)\nCharacterActorLocation:(%f, %f, %f)\nCharacterSocketLocation(%f, %f, %f)"),MeshSocketLocation.X, MeshSocketLocation.Y, MeshSocketLocation.Z, CharacterActorLocation.X, CharacterActorLocation.Y, CharacterActorLocation.Z, CharacterBaseLocation.X, CharacterBaseLocation.Y, CharacterBaseLocation.Z),4);

	Debug::Print(FString::Printf(
		             TEXT(
			             "�ㅁ�ㅁMeshSocketRotation: (%f, %f, %f)\nCharacterActorRotation:(%f, %f, %f)\nCharacterSocketRotation(%f, %f, %f)"),
		             MeshSocketRotation.Roll, MeshSocketRotation.Pitch, MeshSocketRotation.Yaw,
		             CharacterActorRotation.Roll, CharacterActorRotation.Pitch, CharacterActorRotation.Yaw,
		             CharacterBaseRotation.Roll, CharacterBaseRotation.Pitch, CharacterBaseRotation.Yaw), 5);
	Debug::Print(FString::Printf(
		             TEXT(
			             "�ㅁ�ㅁMeshSocketRotation: (%f, %f, %f)\nCharacterActorRotation:(%f, %f, %f)\nCharacterSocketRotation(%f, %f, %f)"),
		             MeshSocketRotation.Roll, MeshSocketRotation.Pitch, MeshSocketRotation.Yaw,
		             CharacterActorRotation.Roll, CharacterActorRotation.Pitch, CharacterActorRotation.Yaw,
		             CharacterBaseRotation.Roll, CharacterBaseRotation.Pitch, CharacterBaseRotation.Yaw), 5);
	//Debug::Print(FString::Printf(TEXT("11111 MeshSocketRotation: (%f, %f, %f)\nCharacterActorRotation:(%f, %f, %f)\nCharacterSocketRotation(%f, %f, %f)"),MeshSocketRotation.Roll, MeshSocketRotation.Pitch, MeshSocketRotation.Yaw, CharacterActorRotation.Roll, CharacterActorRotation.Pitch, CharacterActorRotation.Yaw, CharacterBaseRotation.Roll, CharacterBaseRotation.Pitch, CharacterBaseRotation.Yaw),5);

	Character->SetActorLocation(MeshSocketLocation + CharacterMeshOffset);


	//Character->SetActorRotation(FRotator(0,MeshSocketRotation.Yaw,0));
	//Character->SetActorRotation(FRotator(0, 0, 0));
	//Character->SetActorLocation(CharacterMeshOffset + FVector(-18.5, -7, -13));
	//Character->SetActorRotation(Mesh->GetSocketRotation(MeshSocket)+ Character->GetActorRotation() - (CharacterMesh->GetSocketRotation(CharacterSocket)));
	//Character->SetActorRotation(Character->GetActorRotation() - (CharacterMesh->GetSocketRotation(CharacterSocket)) + FRotator(-8.84, -30, -82));
	Character->AttachToComponent(Mesh, FAttachmentTransformRules::KeepWorldTransform, MeshSocket);
	return;
}

void UDBDBlueprintFunctionLibrary::AttachCharacterWithRotationAdjust(USkeletalMeshComponent* Mesh, FName MeshSocket,
                                                                     ADBDCharacter* Character, FRotator Offset,
                                                                     FName CharacterSocket)
{
	Character->K2_DetachFromActor(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld);


	if (!Character || !Mesh || !Mesh->DoesSocketExist(MeshSocket))
	{
		Debug::Print(TEXT("JMS11 : AttachDBDCharacterToSocket() : Invalid Parameter"), 11);
		return;
	}

	USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
	FVector MeshSocketLocation = Mesh->GetSocketLocation(MeshSocket);
	FVector CharacterBaseLocation = CharacterMesh->GetSocketLocation(CharacterSocket);
	FVector CharacterMeshOffset = Character->GetActorLocation() - CharacterBaseLocation;
	FVector CharacterActorLocation = Character->GetActorLocation();
	// DrawDebugSphere(Character->GetWorld(), MeshSocketLocation, 10, 12, FColor::Red, true);
	// DrawDebugSphere(Character->GetWorld(), CharacterBaseLocation, 10, 12, FColor::Blue, true);
	// DrawDebugSphere(Character->GetWorld(), CharacterActorLocation, 10, 12, FColor::Green, true);
	// DrawDebugSphere(Character->GetWorld(), MeshSocketLocation + CharacterMeshOffset, 10, 12, FColor::Yellow, true);

	FRotator MeshSocketRotation = Mesh->GetSocketRotation(MeshSocket);
	FRotator CharacterBaseRotation = CharacterMesh->GetSocketRotation(CharacterSocket);

	Character->SetActorLocation(MeshSocketLocation + CharacterMeshOffset);
	Character->SetActorRotation(FRotator(0, MeshSocketRotation.Yaw, 0) + Offset);
	Character->AttachToComponent(Mesh, FAttachmentTransformRules::KeepWorldTransform, MeshSocket);
	return;
}
