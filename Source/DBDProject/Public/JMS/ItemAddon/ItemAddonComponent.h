// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JMS/Item/SurvivorItem.h"
#include "ItemAddonComponent.generated.h"


class UGameplayEffect;
class ASurvivorItem;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DBDPROJECT_API UItemAddonComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UItemAddonComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemAddon")
	FName AddonID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemAddon")
	TArray<TSubclassOf<UGameplayEffect>> AddonEffects;

public:
	UFUNCTION(BlueprintNativeEvent, Category = "ItemAddon")
	void OnEquip();

	UFUNCTION(BlueprintCallable, Category = "ItemAddon")
	FName GetAddonID() const;

	UFUNCTION(BlueprintNativeEvent, Category = "ItemAddon")
	void OnUnEquip();

	UFUNCTION(BlueprintNativeEvent, Category = "ItemAddon")
	void OnInitialized();

protected:
	template <class T>
	T* GetOwningItem() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, ASurvivorItem>::Value,
					  "'T' Template Parameter must be derived from ASurvivorItem");
		return CastChecked<T>(GetOwner());
	}
	
	ASurvivorItem* GetOwningItem() const
	{
		return GetOwningItem<ASurvivorItem>();
	}
};
