// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "CharacterExtensionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DBDPROJECT_API UCharacterExtensionComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	template <class T>
	T* GetOwningCharacter() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, ACharacter>::Value,
					  "'T' Template Parameter get GetCharacter must be derived from ACharacter");
		return CastChecked<T>(GetOwner());
	}

	ACharacter* GetOwningCharacter() const
	{
		return GetOwningCharacter<ACharacter>();
	}

	template<class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value,
					  "'T' Template Parameter get GetController must be derived from AController");
		return GetOwningCharacter<ACharacter>()->GetController<T>();
	}

	AController* GetOwningController() const
	{
		return GetOwningController<AController>();
	}
};
