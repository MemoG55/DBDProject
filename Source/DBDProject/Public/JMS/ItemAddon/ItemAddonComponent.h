// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemAddonComponent.generated.h"


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

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintNativeEvent, Category = "ItemAddon")
	void OnInitialized();

	UFUNCTION(BlueprintCallable, Category = "ItemAddon")
	FName GetAddonID() const;

protected:
	// template <class T>
	// T* GetOwningItem() const
	// {
	// 	static_assert(TPointerIsConvertibleFromTo<T, ASurvivorItem>::Value,
	// 				  "'T' Template Parameter must be derived from ASurvivorItem");
	// 	return CastChecked<T>(GetOwner());
	// }
	//
	// ASurvivorItem* GetOwningItem() const
	// {
	// 	return GetOwningItem<ASurvivorItem>();
	// }
	// 	
};
