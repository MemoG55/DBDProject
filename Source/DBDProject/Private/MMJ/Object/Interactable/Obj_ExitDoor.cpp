// Fill out your copyright notice in the Description page of Project Settings.


#include "MMJ/Object/Interactable/Obj_ExitDoor.h"

#include "MMJ/Object/GAS/ObjAbilitySystemComponent.h"
#include "Shared/DBDBlueprintFunctionLibrary.h"
#include "Shared/DBDGameplayTags.h"

bool AObj_ExitDoor::CanInteraction(AActor* Actor)
{
	if (ObjAbilitySystemComponent)
	{
		// 상호작용이 가능한 경우는 총 2가지
		// 1. CurrentTask != MaxTask ( IsComplete 태그가 붙지 않은 경우)
		// 2. 발전기가 모두 돌아갔을 경우 bCanActive == true (GameState에서 제어)
		if ( GetCanActive() && !UDBDBlueprintFunctionLibrary::NativeActorHasTag(this, DBDGameplayTags::Object_Status_IsComplete))
		{
			return true;
		}
		
	}
	return false;
}
