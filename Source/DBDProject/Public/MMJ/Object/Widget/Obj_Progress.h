// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/UI/DBDProgressBarBase.h"
#include "Obj_Progress.generated.h"

struct FOnAttributeChangeData;
struct FGameplayAttribute;
class UImage;
class UProgressBar;
class UObjAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UObj_Progress : public UDBDProgressBarBase
{
	GENERATED_BODY()
public:
	virtual void SetObjectASC(UDBDAbilitySystemComponent* ASC, const FGameplayAttribute& CurrentAttribute, const FGameplayAttribute& MaxAttribute) override;

protected:
	virtual void NativeConstruct() override;

	virtual void Update() override;

	void UpdateRecoverValue(const FOnAttributeChangeData& ChangeData);

	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UImage* RecoverProgressMarking;

private:
	float CachedRecoverValue;
};
