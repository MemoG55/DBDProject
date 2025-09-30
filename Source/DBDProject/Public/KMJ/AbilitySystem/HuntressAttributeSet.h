// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KMJ/AbilitySystem/KillerAttributeSet.h"
#include "HuntressAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAxeNumberChangedDelegate, float, NewAxeNumber);

UCLASS()
class DBDPROJECT_API UHuntressAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UHuntressAttributeSet();
	
	//자장가 범위
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_LullabyRadiusRange)
	FGameplayAttributeData LullabyRadiusRange;
	ATTRIBUTE_ACCESSORS(UHuntressAttributeSet, LullabyRadiusRange);
	UFUNCTION()
	void OnRep_LullabyRadiusRange(const FGameplayAttributeData& OldValue) const;

	//보유할 수 있는 투척도끼 개수
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_AxeNumber)
	FGameplayAttributeData AxeNumber;
	ATTRIBUTE_ACCESSORS(UHuntressAttributeSet, AxeNumber);
	UFUNCTION()
	void OnRep_AxeNumber(const FGameplayAttributeData& OldValue) const;
	UFUNCTION(BlueprintCallable)
	void SetCurrentAxeNum(float NewAxeNum);
	UPROPERTY(BlueprintAssignable, Category = "Axe")
	FAxeNumberChangedDelegate OnAxeNumberChanged;

	//투척도끼 캐비넷 충전 시간(애니메이션 재생 Rate)
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_RefillAxeFromCabinetRate)
	FGameplayAttributeData RefillAxeFromCabinetRate;
	ATTRIBUTE_ACCESSORS(UHuntressAttributeSet, RefillAxeFromCabinetRate);
	UFUNCTION()
	void OnRep_RefillAxeFromCabinetRate(const FGameplayAttributeData& OldValue) const;
	
	//투척도끼 차징 최소 시간(시간: 초 단위)
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_ChargingAxeMinRate)
	FGameplayAttributeData ChargingAxeMinRate;
	ATTRIBUTE_ACCESSORS(UHuntressAttributeSet, ChargingAxeMinRate);
	UFUNCTION()
	void OnRep_ChargingAxeMinRate(const FGameplayAttributeData& OldValue) const;
	
	//투척도끼 차징 최대 시간(시간: 초 단위)
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_ChargingAxeMaxRate)
	FGameplayAttributeData ChargingAxeMaxRate;
	ATTRIBUTE_ACCESSORS(UHuntressAttributeSet, ChargingAxeMaxRate);
	UFUNCTION()
	void OnRep_ChargingAxeMaxRate(const FGameplayAttributeData& OldValue) const;
	
	//투척도끼 최대 속도(m/s)
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_AxeMaxSpeed)
	FGameplayAttributeData AxeMaxSpeed;
	ATTRIBUTE_ACCESSORS(UHuntressAttributeSet, AxeMaxSpeed);
	UFUNCTION()
	void OnRep_AxeMaxSpeed(const FGameplayAttributeData& OldValue) const;
	
	//투척도끼 최소 속도(m/s)
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_AxeMinSpeed)
	FGameplayAttributeData AxeMinSpeed;
	ATTRIBUTE_ACCESSORS(UHuntressAttributeSet, AxeMinSpeed);
	UFUNCTION()
	void OnRep_AxeMinSpeed(const FGameplayAttributeData& OldValue) const;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
