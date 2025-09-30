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
	None		UMETA(DisplayName = "None"),
	Attack		UMETA(DisplayName = "Attack"),
	Skill		UMETA(DisplayName = "Skill"),
	Interact	UMETA(DisplayName = "Interact"),
	Drop		UMETA(DisplayName = "Drop"),
	Carry		UMETA(DisplayName = "Carry"),
	Hook 		UMETA(DisplayName = "Hook"),
	Totem 		UMETA(DisplayName = "Totem"),
	Window		UMETA(DisplayName = "Window"),
	Locker 		UMETA(DisplayName = "Locker"),
	Door 		UMETA(DisplayName = "Door"),
	Hatch 		UMETA(DisplayName = "Hatch"),
	Generator 	UMETA(DisplayName = "Generator")
};

UENUM(BlueprintType)
enum class ESurvivorAbilityInputID : uint8
{
	None		UMETA(DisplayName = "None"),
	RepairGenerator		UMETA(DisplayName = "RepairGenerator"),
	HealOtherSurvivor	UMETA(DisplayName = "HealOtherSurvivor"),
	OpenGate		UMETA(DisplayName = "OpenGate"),
	UseItem		UMETA(DisplayName = "UseItem"),
	DropItem		UMETA(DisplayName = "DropItem"),
	SkillCheck		UMETA(DisplayName = "SkillCheck"),
};

UENUM(BlueprintType)
enum class ESkillCheckResult : uint8
{
	Good,
	Great,
	Bad
};

class DBDPROJECT_API DBDEnum
{
public:
};
