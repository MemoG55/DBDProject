#pragma once
#include "DBDEnum.h"
#include "DBDStruct.generated.h"

class UPerkComponent;
class UItemAddonComponent;
class ASurvivorItem;
class IInteractable;
class UInputMappingContext;
class ASurvivorCharacter;
class ADBDCharacter;
enum class ETier:uint8;
enum class EIconEffect:uint8;

USTRUCT(BlueprintTYpe)
struct FSurvivorItemInstanceInfo
{
	//YHG:ReadWrite
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Item = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Addon1 = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Addon2 = NAME_None;
};

USTRUCT(BlueprintType)
struct FSurvivorLoadout
{
	GENERATED_BODY()

	//YHG:ReadWrite
	UPROPERTY(EditAnywhere)
	FName Character = FName("ClaudetteMorel");
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSurvivorItemInstanceInfo ItemInfo = FSurvivorItemInstanceInfo();
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	FName Perk1 = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Perk2 = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Perk3 = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Perk4 = NAME_None;
	UPROPERTY(EditAnywhere)
	FName Offering = NAME_None;
	// JMS: UI수정: Array로 안 담아서 죄송합니다 ㅠㅠ DBDGameMode에서 위에있는 정보를 담았습니다.
	UPROPERTY()
	TArray<FName> Perks = { NAME_None, NAME_None, NAME_None, NAME_None };
	UPROPERTY()
	TArray<FName> ItemAddons;

	void PerkInitialize()
	{
		Perks.Empty();
		Perks.Add(Perk1);
		Perks.Add(Perk2);
		Perks.Add(Perk3);
		Perks.Add(Perk4);
	}
};


USTRUCT(BlueprintType)
struct FPerkData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FText DisplayName = FText();
	UPROPERTY(EditAnywhere)
	ETier Tier = ETier::Blue;
	UPROPERTY(EditAnywhere)
	FText Description = FText();
	UPROPERTY(EditAnywhere)
	FText Lore = FText();
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTexture2D> Icon = nullptr;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPerkComponent> PerkClass = nullptr;
	UPROPERTY(EditAnywhere)
	bool IsStackable = false;
	UPROPERTY(EditAnywhere)
	int32 Stack = 0;
	UPROPERTY(EditAnywhere)
	EIconEffect Effect = EIconEffect::None;
	
	bool operator ==(const FPerkData& Other) const
	{
		return DisplayName.EqualTo(Other.DisplayName) && Tier == Other.Tier && Description.EqualTo(Other.Description) && Lore.EqualTo(Other.Lore)
				&& Icon == Other.Icon && IsStackable == Other.IsStackable
				&& Stack == Other.Stack && Effect == Other.Effect;
	}
};
USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	FName Category = NAME_None;
	//YHG251020 : �단 BP�서 메인메뉴 �이�공 UI�만들긄해 BlueprintReadOnly�붙여�겠
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DisplayName = FText();
	UPROPERTY(EditAnywhere)
	ETier Tier = ETier::Blue;
	UPROPERTY(EditAnywhere)
	FText Description = FText();
	UPROPERTY(EditAnywhere)
	FText Lore = FText();
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTexture2D> Icon = nullptr;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASurvivorItem> ItemClass = nullptr;
	UPROPERTY(EditAnywhere)
	EIconEffect Effect = EIconEffect::None;

	bool operator ==(const FItemData& Other) const
	{
		return DisplayName.EqualTo(Other.DisplayName) && Tier == Other.Tier && Description.EqualTo(Other.Description) && Lore.EqualTo(Other.Lore)
				&& Icon == Other.Icon && Category == Other.Category && Effect == Other.Effect;
	}
};
USTRUCT(BlueprintType)
struct FItemAddonData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	FName Category = NAME_None;
	UPROPERTY(EditAnywhere)
	FText DisplayName = FText();
	UPROPERTY(EditAnywhere)
	ETier Tier = ETier::Blue;
	UPROPERTY(EditAnywhere)
	FText Description = FText();
	UPROPERTY(EditAnywhere)
	FText Lore = FText();
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTexture2D> Icon = nullptr;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemAddonComponent> AddonClass = nullptr;

	bool operator ==(const FItemAddonData& Other) const
	{
		return DisplayName.EqualTo(Other.DisplayName) && Tier == Other.Tier && Description.EqualTo(Other.Description) && Lore.EqualTo(Other.Lore)
				&& Icon == Other.Icon && Category == Other.Category;
	}
};
USTRUCT(BlueprintType)
struct FKillerLoadout
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FName Character = NAME_None;
	UPROPERTY(EditAnywhere)
	FName Addon1 = NAME_None;
	UPROPERTY(EditAnywhere)
	FName Addon2 = NAME_None;
	UPROPERTY(EditAnywhere)
	FName Perk1 = NAME_None;
	UPROPERTY(EditAnywhere)
	FName Perk2 = NAME_None;
	UPROPERTY(EditAnywhere)
	FName Perk3 = NAME_None;
	UPROPERTY(EditAnywhere)
	FName Perk4 = NAME_None;
	UPROPERTY(EditAnywhere)
	FName Offering = NAME_None;
	// JMS: UI수정: Array로 안 담아서 죄송합니다 ㅠㅠ DBDGameMode에서 위에있는 정보를 담았습니다.
	UPROPERTY()
	TArray<FName> Perks = { NAME_None, NAME_None, NAME_None, NAME_None };
	UPROPERTY()
	TArray<FName> Addons;

	void PerkInitialize()
	{
		Perks.Empty();
		Perks.Add(Perk1);
		Perks.Add(Perk2);
		Perks.Add(Perk3);
		Perks.Add(Perk4);
	}
};

USTRUCT(BlueprintType)
struct FSurvivorBaseStat : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASurvivorCharacter> CharacterClass = nullptr;
	UPROPERTY(EditAnywhere)
	float MaxHookHP = 0.f;
	UPROPERTY(EditAnywhere)
	float MaxDyingHP = 0.f;
	UPROPERTY(EditAnywhere)
	float MaxHealProgress = 0.f;
	UPROPERTY(EditAnywhere)
	float MovementSpeed = 0.f;
	UPROPERTY(EditAnywhere)
	float GeneratorRepairSpeed = 0.f;
};
USTRUCT(BlueprintType)
struct FInteractionInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInputMappingContext> InputMappingContext = nullptr;
	UPROPERTY(EditAnywhere)
	TWeakObjectPtr<IInteractable> Interactable = nullptr;
};

USTRUCT(BlueprintType)
struct FMotionWarpingInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName WarpTargetName = NAME_None;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USceneComponent> Component = nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName BoneName = NAME_None;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bFollowComponent = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector LocationOffset = FVector::ZeroVector;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FRotator RotationOffset = FRotator::ZeroRotator;
};

USTRUCT()
struct FAxeCollisionLocation
{
	GENERATED_BODY()
public:
	FVector StartLocation = FVector::ZeroVector;
	FVector EndLocation = FVector::ZeroVector;
};

USTRUCT(BlueprintType)
struct FStencilMap
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY()
	int32 StencilValue = 0;

	UPROPERTY()
	bool bUseBackground = false;

	bool operator==(const FStencilMap& Other) const
	{
		return PlayerState == Other.PlayerState && StencilValue == Other.StencilValue && bUseBackground == Other.bUseBackground;
	}
};
USTRUCT(BlueprintType)
struct FSurvivorCharacterData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASurvivorCharacter> CharacterClass = nullptr;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTexture2D> CharacterPortrait = nullptr;
};
