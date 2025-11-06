// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/Component/DBDMotionWarpingComponent.h"

#include "GameFramework/Character.h"
#include "Shared/DBDDebugHelper.h"
#include "Shared/DBDStruct.h"


FTransform UDBDMotionWarpingComponent::FindMotionWarpingTargetTransform(const FName& WarpTargetName)
{
	const FMotionWarpingTarget* Target = FindWarpTarget(WarpTargetName);
	if (!Target)
	{
		return FTransform();
	}
	return Target->GetTargetTransformFromComponent(Target->Component.Get(), Target->BoneName);
}

void UDBDMotionWarpingComponent::SetOwnerLocationAndRotationUsingWarpTarget(const FName& WarpTargetName)
{
	const FMotionWarpingTarget* Target = FindWarpTarget(WarpTargetName);
	if (!Target)
	{
		return;
	}
	GetCharacterOwner()->K2_DetachFromActor(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld,
	                                        EDetachmentRule::KeepWorld);

	USkeletalMeshComponent* CharacterMesh = GetCharacterOwner()->GetMesh();
	FVector MeshSocketLocation = Target->Component->GetSocketLocation(Target->BoneName);
	FVector TargetLocation = MeshSocketLocation + Target->LocationOffset;
	// Debug::Print(111111111,TEXT("JMS1111111111: Component: %s, Bone: %s, Location: %s"),*Target->Component->GetName(),*Target->BoneName.ToString(),*MeshSocketLocation.ToString());
	FVector CharacterBaseLocation = CharacterMesh->GetSocketLocation(FName(TEXT("joint_Char")));
	FVector CharacterMeshOffset = GetCharacterOwner()->GetActorLocation() - CharacterBaseLocation;
	// DrawDebugSphere(GetCharacterOwner()->GetWorld(), CharacterBaseLocation, 10, 12, FColor::MakeRandomColor(), true);
	// DrawDebugSphere( GetCharacterOwner()->GetWorld(), CharacterBaseLocation, 10, 12, FColor::Blue, true);
	// DrawDebugSphere( GetCharacterOwner()->GetWorld(), CharacterActorLocation, 10, 12, FColor::Green, true);
	// DrawDebugSphere( GetCharacterOwner()->GetWorld(), MeshSocketLocation + CharacterMeshOffset, 10, 12, FColor::Yellow, true);


	FRotator MeshSocketRotation = Target->Component->GetSocketRotation(Target->BoneName);
	FRotator TargetRotation = MeshSocketRotation - Target->RotationOffset;
	FRotator CharacterBaseRotation = GetCharacterOwner()->GetMesh()->GetComponentRotation();
	FRotator CharacterMeshRotation = GetCharacterOwner()->GetActorRotation() - CharacterBaseRotation;
	FRotator CharacterActorRotation = GetCharacterOwner()->GetActorRotation();
	GetCharacterOwner()->SetActorRotation(TargetRotation);
	GetCharacterOwner()->SetActorLocation(MeshSocketLocation - Target->LocationOffset + CharacterMeshOffset);
	// FHitResult HitResult;
	// GetCharacterOwner()->K2_AddActorWorldOffset(CharacterMeshOffset,false,HitResult,true);
	// GetCharacterOwner()->AddActorWorldRotation(TargetRotation - CharacterBaseRotation);
	// GetCharacterOwner()->SetActorRotation(MeshSocketRotation - Target->RotationOffset);
}
