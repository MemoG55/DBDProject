#pragma once
#include "DBDStruct.generated.h"

class UItemAddonComponent;
class ASurvivorItem;
class IInteractable;
class UInputMappingContext;
class UPerkInstance;
class ASurvivorCharacter;
class ADBDCharacter;

USTRUCT(BlueprintTYpe)
struct FSurvivorItemInstanceInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	FName Item;
	UPROPERTY(EditAnywhere)
	FName Addon1;
	UPROPERTY(EditAnywhere)
	FName Addon2;
};

USTRUCT(BlueprintType)
struct FSurvivorLoadout
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName Character;
	UPROPERTY(EditAnywhere)
	FSurvivorItemInstanceInfo ItemInfo;
	UPROPERTY(EditAnywhere)
	FName Perk1;
	UPROPERTY(EditAnywhere)
	FName Perk2;
	UPROPERTY(EditAnywhere)
	FName Perk3;
	UPROPERTY(EditAnywhere)
	FName Perk4;
	UPROPERTY(EditAnywhere)
	FName Offering;
};

USTRUCT(BlueprintType)
struct FPerkData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FText DisplayName;
	UPROPERTY(EditAnywhere)
	int Tier;
	UPROPERTY(EditAnywhere)
	FText Description;
	UPROPERTY(EditAnywhere)
	FText Lore;
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTexture2D> Icon;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPerkInstance> PerkClass;
};
USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FText DisplayName;
	UPROPERTY(EditAnywhere)
	int Tier;
	UPROPERTY(EditAnywhere)
	FText Description;
	UPROPERTY(EditAnywhere)
	FText Lore;
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTexture2D> Icon;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASurvivorItem> ItemClass;
};
USTRUCT(BlueprintType)
struct FItemAddonData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FText DisplayName;
	UPROPERTY(EditAnywhere)
	int Tier;
	UPROPERTY(EditAnywhere)
	FText Description;
	UPROPERTY(EditAnywhere)
	FText Lore;
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTexture2D> Icon;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemAddonComponent> AddonClass;
};

USTRUCT(BlueprintType)
struct FKillerLoadout
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FName Character;
	UPROPERTY(EditAnywhere)
	FName Addon1;
	UPROPERTY(EditAnywhere)
	FName Addon2;
	UPROPERTY(EditAnywhere)
	FName Perk1;
	UPROPERTY(EditAnywhere)
	FName Perk2;
	UPROPERTY(EditAnywhere)
	FName Perk3;
	UPROPERTY(EditAnywhere)
	FName Perk4;
	UPROPERTY(EditAnywhere)
	FName Offering;
};

USTRUCT(BlueprintType)
struct FSurvivorBaseStat : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASurvivorCharacter> CharacterClass;
	UPROPERTY(EditAnywhere)
	float MaxHookHP;
	UPROPERTY(EditAnywhere)
	float MaxDyingHP;
	UPROPERTY(EditAnywhere)
	float MaxHealProgress;
	UPROPERTY(EditAnywhere)
	float MovementSpeed;
	UPROPERTY(EditAnywhere)
	float GeneratorRepairSpeed;
};
USTRUCT(BlueprintType)
struct FInteractionInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere)
	TWeakObjectPtr<IInteractable> Interactable;
};