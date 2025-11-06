#include "Shared/DBDGameplayTags.h"

namespace DBDGameplayTags
{
	// Survivor Status
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Normal, "Survivor.Status.Normal");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Injured, "Survivor.Status.Injured");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Dying, "Survivor.Status.Dying");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_CaptureEnabled, "Survivor.Status.CaptureEnabled");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_HookedPhase2, "Survivor.Status.HookedPhase2");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_HookCount, "Survivor.Status.HookCount");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Moving, "Survivor.Status.Moving");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Crouched, "Survivor.Status.Crouched");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Sprinting, "Survivor.Status.Sprinting");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_SprintEnabled, "Survivor.Status.SprintEnabled");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Dead, "Survivor.Status.Dead");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Escaped, "Survivor.Status.Escaped");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_MoveDisabled, "Survivor.Status.MoveDisabled");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Aiming, "Survivor.Status.Aiming");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_BeingHealed, "Survivor.Status.BeingHealed");
	//Survivor Status (Captured)
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Captured_Killer, "Survivor.Status.Captured.Killer");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Captured_Cabinet, "Survivor.Status.Captured.Cabinet");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Captured_Hook, "Survivor.Status.Captured.Hook");
	//Survivor Status (Effect)
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Exhausted, "Survivor.Status.Exhausted");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Buff_RepairSpeed, "Survivor.Status.Buff.RepairSpeed");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_SprintBurst, "Survivor.Status.SprintBurst");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Adrenaline, "Survivor.Status.Adrenaline");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_BotanyKnowledge, "Survivor.Status.BotanyKnowledge");
	
	// Survivor Base Ability
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_EnableSprint, "Survivor.Ability.EnableSprint");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Move, "Survivor.Ability.Move");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_DropItem, "Survivor.Ability.DropItem");
	
	// Survivor Passive Ability
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Passive_CapturedByKiller, "Survivor.Ability.Passive.CapturedByKiller");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Passive_HookedIn, "Survivor.Ability.Passive.HookedIn");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Passive_Hooked, "Survivor.Ability.Passive.Hooked");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Passive_Escape, "Survivor.Ability.Passive.Escape");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Passive_Sprint, "Survivor.Ability.Passive.Sprint");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Passive_CapturedByCabinet, "Survivor.Ability.Passive.CapturedByCabinet");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Passive_Dying, "Survivor.Ability.Passive.Dying");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Passive_Crouch, "Survivor.Ability.Passive.Crouch");
	// Survivor Interaction Ability
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Interaction_RepairGenerator,
	                       "Survivor.Ability.Interaction.RepairGenerator");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Interaction_OpenExitDoor, "Survivor.Ability.Interaction.OpenExitDoor");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Interaction_HealOther, "Survivor.Ability.Interaction.HealOther");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Interaction_Rescue, "Survivor.Ability.Interaction.Rescue");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Interaction_PickUpItem, "Survivor.Ability.Interaction.PickUpItem");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Interaction_OpenCabinet, "Survivor.Ability.Interaction.OpenCabinet");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Interaction_Test, "Survivor.Ability.Interaction.Test");
	// Survivor UseItem Ability
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_UseItem_UseFireCracker, "Survivor.Ability.UseItem.UseFireCracker");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_UseItem_ToolboxRepair, "Survivor.Ability.UseItem.ToolboxRepair");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_UseItem_ToolboxSabotage, "Survivor.Ability.UseItem.ToolboxSabotage");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_UseItem_MedKitHealOther, "Survivor.Ability.UseItem.MedKitHealOther");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_UseItem_MedKitHealSelf, "Survivor.Ability.UseItem.MedKitHealSelf");
	// Survivor Perk Ability
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Perk_HealSelf, "Survivor.Ability.Perk.HealSelf");
	// Survivor Perk Effect
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Effect_Perk_QuickAndQuiet, "Survivor.Effect.Perk.QuickAndQuiet");
	// Survivor Item
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Item_FireCracker, "Survivor.Item.FireCracker");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Item_Toolbox, "Survivor.Item.Toolbox");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Item_MedKit, "Survivor.Item.MedKit");
	// Survivor Item Status
	UE_DEFINE_GAMEPLAY_TAG(Item_Status_Using, "Item.Status.Using");

	// Survivor SetbyCaller
	UE_DEFINE_GAMEPLAY_TAG(Survivor_SetbyCaller_HealAmount, "Survivor.SetbyCaller.HealAmount");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_SetbyCaller_Multiplier1, "Survivor.SetbyCaller.Multiplier1");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_SetbyCaller_Multiplier2, "Survivor.SetbyCaller.Multiplier2");

	// Survivor GameplayEvent
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Event_RescueFromHook, "Survivor.Event.RescueFromHook");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Event_GetHit, "Survivor.Event.GetHit");

	//Killer
	UE_DEFINE_GAMEPLAY_TAG(Killer_Name_Huntress, "Killer.Name.Huntress");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Name_Nurse, "Killer.Name.Nurse");

	//Killer_Ability
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Attack, "Killer.Common.Ability.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Skill, "Killer.Common.Ability.Skill");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Carry, "Killer.Common.Ability.Interaction.Carry");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Drop, "Killer.Common.Ability.Interaction.Drop");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Hook, "Killer.Common.Ability.Interaction.Hook");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Kick_Totem,
	                       "Killer.Common.Ability.Interaction.Kick.Totem");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Kick_Generator,
	                       "Killer.Common.Ability.Interaction.Kick.Generator");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Kick_Pallet,
	                       "Killer.Common.Ability.Interaction.Kick.Pallet");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Loker, "Killer.Common.Ability.Interaction.Locker");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Hatch, "Killer.Common.Ability.Interaction.Hatch");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Door, "Killer.Common.Ability.Interaction.Door");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Window, "Killer.Common.Ability.Interaction.Window");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Test, "Killer.Common.Ability.Interaction.Test");

	//Killer_Status
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Status_Stunned, "Killer.Common.Status.Stunned");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Status_Attacking, "Killer.Common.Status.Attacking");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Status_SkillAttacking, "Killer.Common.Status.SkillAttacking");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Status_Falling, "Killer.Common.Status.Falling");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Status_Normal, "Killer.Common.Status.Normal");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Status_Carrying, "Killer.Common.Status.Carrying");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Status_Dropping, "Killer.Common.Status.Dropping");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Status_Hooking, "Killer.Common.Status.Hooking");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Status_Kicking, "Killer.Common.Status.Kicking");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Status_Interacting, "Killer.Common.Status.Interacting");

	//Killer_Huntress_Status
	UE_DEFINE_GAMEPLAY_TAG(Killer_Huntress_Status_AxeCharging, "Killer.Huntress.Status.AxeCharging");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Huntress_Status_AxeRefilling, "Killer.Huntress.Status.AxeRefilling");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Huntress_Status_AxeEmpty, "Killer.Huntress.Status.AxeEmpty");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Huntress_Status_AxeFull, "Killer.Huntress.Status.AxeFull");

	//Killer_Event
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Event_Attack, "Killer.Common.Event.Attack");

#pragma region Object:
	// Object
	UE_DEFINE_GAMEPLAY_TAG(Object_Status_IsActive, "Object.Status.IsActive");
	UE_DEFINE_GAMEPLAY_TAG(Object_Status_IsInActive, "Object.Status.IsInActive");
	UE_DEFINE_GAMEPLAY_TAG(Object_Status_IsDestroy, "Object.Status.IsDestroy");
	UE_DEFINE_GAMEPLAY_TAG(Object_Status_IsComplete, "Object.Status.IsComplete");

	// Object Progress
	UE_DEFINE_GAMEPLAY_TAG(Object_Progress_Complete, "Object.Progress.Complete");
	UE_DEFINE_GAMEPLAY_TAG(Object_Progress_OnProgress, "Object.Progress.OnProgress");
	UE_DEFINE_GAMEPLAY_TAG(Object_Progress_ActorCount, "Object.Progress.ActorCount");
	UE_DEFINE_GAMEPLAY_TAG(Object_Progress_Speed, "Object.Progress.Speed");
	UE_DEFINE_GAMEPLAY_TAG(Object_Progress_Speed_Generator, "Object.Progress.Speed.Generator");
	UE_DEFINE_GAMEPLAY_TAG(Object_Progress_Speed_Hook, "Object.Progress.Speed.Hook");
	UE_DEFINE_GAMEPLAY_TAG(Object_Progress_Speed_ExitDoor, "Object.Progress.Speed.ExitDoor");

	// Object SkillChek
	UE_DEFINE_GAMEPLAY_TAG(Object_Event_Interact, "Object.Event.Interact");
	UE_DEFINE_GAMEPLAY_TAG(Object_Event_Check, "Object.Event.Check");
	UE_DEFINE_GAMEPLAY_TAG(Object_Event_Result_Success, "Object.Event.Result.Success");
	UE_DEFINE_GAMEPLAY_TAG(Object_Event_Result_Failure, "Object.Event.Result.Failure");

#pragma endregion
	
	// 방향�그�데 공통�로 �질맠것같아추�습�다(MMJ)
	UE_DEFINE_GAMEPLAY_TAG(Shared_Direction_Default, "Shared.Direction.Default");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Direction_Front, "Shared.Direction.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Direction_Back, "Shared.Direction.Back");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Direction_Left, "Shared.Direction.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Direction_Right, "Shared.Direction.Right");

	// Shared Status
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Blind, "Shared.Status.Blind");

	// Shared Event
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Blind, "Shared.Event.Blind");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Attach, "Shared.Event.Attach");

	// Shared Ability
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Blind, "Shared.Ability.Blind");

	// GameState
	UE_DEFINE_GAMEPLAY_TAG(Shared_GameState_End, "Shared.GameState.End");

	// Interactable
	UE_DEFINE_GAMEPLAY_TAG(Interactable_Object_Generator, "Interactable.Object.Generator");
	UE_DEFINE_GAMEPLAY_TAG(Interactable_Object_Hook, "Interactable.Object.Hook");
	UE_DEFINE_GAMEPLAY_TAG(Interactable_Object_ExitDoor, "Interactable.Object.ExitDoor");
	UE_DEFINE_GAMEPLAY_TAG(Interactable_Object_Exit, "Interactable.Object.Exit");
	UE_DEFINE_GAMEPLAY_TAG(Interactable_Object_Crow, "Interactable.Object.Crow");
	UE_DEFINE_GAMEPLAY_TAG(Interactable_Object_Cabinet, "Interactable.Object.Cabinet");
	UE_DEFINE_GAMEPLAY_TAG(Interactable_Object_Chest, "Interactable.Object.Chest");
	UE_DEFINE_GAMEPLAY_TAG(Interactable_Object_Pallet, "Interactable.Object.Pallet");
	UE_DEFINE_GAMEPLAY_TAG(Interactable_Object_Frame, "Interactable.Object.Frame");
	UE_DEFINE_GAMEPLAY_TAG(Interactable_Object_Window, "Interactable.Object.Window");
	UE_DEFINE_GAMEPLAY_TAG(Interactable_Object_SurvivorItem, "Interactable.Object.SurvivorItem");
	UE_DEFINE_GAMEPLAY_TAG(Interactable_Character_Survivor, "Interactable.Character.Survivor");
	UE_DEFINE_GAMEPLAY_TAG(Interactable_Character_Killer, "Interactable.Character.Killer");
}
