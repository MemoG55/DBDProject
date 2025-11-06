// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
UENUM(BlueprintType)
enum class EPlayerRole : uint8
{
	Survivor	UMETA(DisplayName = "Survivor"),
	Killer		UMETA(DisplayName = "Killer"),
};


UENUM(BlueprintType)
enum class EKillerName : uint8
{
	Huntress	UMETA(DisplayName = "Huntress"),
	Nurse		UMETA(DisplayName = "Nurse"),
};

UENUM(BlueprintType)
enum class EKillerAbilityInputID : uint8
{
	None		    UMETA(DisplayName = "None"),
	Attack			UMETA(DisplayName = "Attack"),
	CarryingAttack 	UMETA(DisplayName = "CarringAttack"),
	Skill			UMETA(DisplayName = "Skill"),
	Interact		UMETA(DisplayName = "Interact"),
	Drop			UMETA(DisplayName = "Drop"),
	Carry			UMETA(DisplayName = "Carry"),
	Hook 			UMETA(DisplayName = "Hook"),
	Totem 			UMETA(DisplayName = "Totem"),
	Window			UMETA(DisplayName = "Window"),
	Locker 			UMETA(DisplayName = "Locker"),
	Door 			UMETA(DisplayName = "Door"),
	Hatch 			UMETA(DisplayName = "Hatch"),
	Generator 		UMETA(DisplayName = "Generator"),
	Test			UMETA(DisplayName = "Test")
};

UENUM(BlueprintType)
enum class ESurvivorAbilityInputID : uint8
{
	None				UMETA(DisplayName = "None"),
	RepairGenerator		UMETA(DisplayName = "RepairGenerator"),
	HealOtherSurvivor	UMETA(DisplayName = "HealOtherSurvivor"),
	OpenGate			UMETA(DisplayName = "OpenGate"),
	UseItem				UMETA(DisplayName = "UseItem"),
	DropItem			UMETA(DisplayName = "DropItem"),
	PickUpItem			UMETA(DisplayName = "PickUpItem"),
	SkillCheck			UMETA(DisplayName = "SkillCheck"),
	Test				UMETA(DisplayName = "Test"),
	SelfCare			UMETA(DisplayName = "SelfCare"),
	Rescue				UMETA(DisplayName = "Rescue"),
	EnableSprint		UMETA(DisplayName = "EnableSprint"),
	Move				UMETA(DisplayName = "Move"),
	OpenCabinet			UMETA(DisplayName = "OpenCabinet"),
	Crouch				UMETA(DisplayName = "Crouch"),
};

UENUM(BlueprintType)
enum class ESkillCheckResult : uint8
{
	Good,
	Great,
	Bad
};

UENUM(BlueprintType)
enum class ETier : uint8
{
	Purple	UMETA(DisplayName = "Purple"),
	Red		UMETA(DisplayName = "Red"),
	Yellow	UMETA(DisplayName = "Yellow"),
	Green	UMETA(DisplayName = "Green"),
	Brown	UMETA(DisplayName = "Brown"),
	Blue	UMETA(DisplayName = "Blue"),
};

UENUM(BlueprintType)
enum class EIconEffect : uint8
{
	None		UMETA(DisplayName = "None"),
	Cooldown	UMETA(DisplayName = "Cooldown"),
	Disable		UMETA(DisplayName = "Disable"),
};


UENUM(BlueprintType)
enum class ELobbyLoadOutSlotType :uint8
{
	None		UMETA(DisplayName = "None"),
	Perk		UMETA(DisplayName = "Perk"),
	Item		UMETA(DisplayName = "Item"),
	AddOn		UMETA(DisplayName = "AddOn"),
};

UENUM(BlueprintType)
enum class EPlayerEndState :uint8
{
	None		UMETA(DisplayName = "None"),
	Sacrifice	UMETA(DisplayName = "Sacrifice"),
	Escape 		UMETA(DisplayName = "Escape"),
	Killer 		UMETA(DisplayName = "Killer"),
};
class DBDPROJECT_API DBDEnum
{
public:
};
