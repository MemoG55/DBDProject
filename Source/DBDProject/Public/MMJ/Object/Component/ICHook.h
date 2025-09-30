// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ICObject.h"
#include "ICHook.generated.h"

class AObj_Hook;
class ADBDCharacter;

UENUM(BlueprintType)
enum class EHookPhase : uint8
{
	Phase_None		UMETA(DisplayName = "Phase None"),	
	Phase_Normal	UMETA(DisplayName = "Phase Normal"),
	Phase_Entity	UMETA(DisplayName = "Phase Entity"),
	Phase_Final		UMETA(DisplayName = "Phase Final"),
};
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UICHook : public UICObject
{
	GENERATED_BODY()
public:
	UICHook();
protected:
	virtual void StartInteraction(AActor* Actor) override;
	virtual void TickInteraction(AActor* Actor) override;
	virtual void FinishInteraction(AActor* Actor) override;
	
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	AObj_Hook* Hook;
	
	UPROPERTY()
	ADBDCharacter* HookedSurvivor;

	UPROPERTY()
	EHookPhase HookPhase = EHookPhase::Phase_None;

public:
	// 갈고리는 살인마가 생존자를 들쳐업은 경우에만 가능
	virtual bool CanInteraction(AActor* Actor) override;
	
	UFUNCTION(BlueprintCallable)
	void SetHookedSurvivor(ADBDCharacter* Actor);

	// 걸려있는 생존자의 HP를 감지하는 델리게이트 핸들
	
	FDelegateHandle HookedSurvivorHPDelegateHandle;
	
	UFUNCTION(BlueprintCallable)
	void UnSetHookedSurvivor(ADBDCharacter* Actor);

	void OnSurvivorHealthUpdated(const FOnAttributeChangeData& OnAttributeChangeData);

	UFUNCTION(BlueprintCallable)
	EHookPhase GetHookPhase();
};
