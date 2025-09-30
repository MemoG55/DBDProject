// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMJ/Object/Widget/ObjWidgetBase.h"
#include "Obj_HUD.generated.h"

class UObjAbilitySystemComponent;
class UObj_Progress;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UObj_HUD : public UObjWidgetBase
{
	GENERATED_BODY()

public:
	void ConfigureASC(UObjAbilitySystemComponent* ASC);
	
	UPROPERTY(meta = (BindWidget))
	UObj_Progress* ProgressBar;
	
};
