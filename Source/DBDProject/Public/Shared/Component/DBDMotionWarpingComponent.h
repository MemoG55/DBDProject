// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MotionWarpingComponent.h"
#include "DBDMotionWarpingComponent.generated.h"

struct FMotionWarpingInfo;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UDBDMotionWarpingComponent : public UMotionWarpingComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	FTransform FindMotionWarpingTargetTransform(const FName& WarpTargetName);
	UFUNCTION(BlueprintCallable)
	void SetOwnerLocationAndRotationUsingWarpTarget(const FName& WarpTargetName);
	
};
