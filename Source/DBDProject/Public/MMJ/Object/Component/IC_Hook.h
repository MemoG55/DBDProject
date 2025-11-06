// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ICObject.h"
#include "Shared/Interface/Capturable.h"
#include "IC_Hook.generated.h"

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
class DBDPROJECT_API UIC_Hook : public UICObject, public ICapturable
{
	GENERATED_BODY()
public:
	UIC_Hook();

	// 갈고리에 걸린 생존자 전처리
	UFUNCTION(BlueprintCallable)
	virtual void Capture(AActor* Actor) override;
	
	virtual void StartInteraction(AActor* Actor) override;
	virtual void TickInteraction(AActor* Actor) override;
	virtual void FinishInteraction(AActor* Actor) override;

	virtual void DestroyInteraction(AActor* Actor) override;
	
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	AObj_Hook* Hook;
public:
	// 갈고리는 살인마가 생존자를 들쳐업은 경우에만 가능
	virtual bool CanInteraction(AActor* Actor) override;
};
