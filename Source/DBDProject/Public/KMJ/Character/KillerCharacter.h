// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/Character/DBDCharacter.h"
#include "KillerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API AKillerCharacter : public ADBDCharacter
{
	GENERATED_BODY()
public:
	AKillerCharacter();
private:
	UPROPERTY(EditDefaultsOnly, Category="Killer_View", meta=(AllowPrivateAccess="true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category="Killer", meta=(AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* HeadSkeletalMesh;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem", meta = (AllowPrivateAccess = "true"))
	
};