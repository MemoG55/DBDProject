// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/UI/BaseIcon.h"
#include "BaseSquareIcon.generated.h"

/**
 * 
 */
UCLASS()
class DBDPROJECT_API UBaseSquareIcon : public UBaseIcon
{
	GENERATED_BODY()
public:
	//아이템 교체할 때 사용
	UFUNCTION()
	void ClearIcon();
	
	UFUNCTION()
	void SetIconLevel(ETier Tier);
	
};
