// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/Perk/PerkComponent.h"
#include "Perk_SelfCare.generated.h"

class UGA_SelfCare;
/**
 * 
 */
UCLASS()
class DBDPROJECT_API UPerk_SelfCare : public UPerkComponent
{
	GENERATED_BODY()
public:
	UPerk_SelfCare();
	virtual void OnServerSideInitialized() override;
	
private:
	UPROPERTY(EditAnywhere,meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGA_SelfCare> SelfCareAbility;
	
};
