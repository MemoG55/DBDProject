// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Widget/Obj_HUD.h"

#include "MMJ/Object/GAS/ObjAttributeSet.h"
#include "MMJ/Object/Widget/Obj_Progress.h"

void UObj_HUD::ConfigureASC(UObjAbilitySystemComponent* ASC)
{
	if (ProgressBar)
	{
		if (ASC)
		{
			ProgressBar->SetObjectASC(ASC, UObjAttributeSet::GetCurrentTaskAttribute(), UObjAttributeSet::GetMaxTaskAttribute());
		}
	}
}
