#include "Shared/DBDGameplayTags.h"

namespace DBDGameplayTags
{
	// Survivor Status
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Normal, "Survivor.Status.Normal");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Injured, "Survivor.Status.Injured");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Dying, "Survivor.Status.Dying");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Captured, "Survivor.Status.Captured");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_CaptureEnabled, "Survivor.Status.CaptureEnabled");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Hooked, "Survivor.Status.Hooked");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_HookCount, "Survivor.Status.HookCount");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Crouched, "Survivor.Status.Crouched");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Dead, "Survivor.Status.Dead");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Escaped, "Survivor.Status.Escaped");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_MoveDisabled, "Survivor.Status.MoveDisabled");
	

	// Survivor Passive Ability
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Passive_CapturedByKiller, "Survivor.Ability.Passive.CapturedByKiller");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Passive_HookedIn, "Survivor.Ability.Passive.HookedIn");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Passive_Hooked, "Survivor.Ability.Passive.Hooked");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Passive_Escape, "Survivor.Ability.Passive.Escape");
	// Survivor Interaction Ability
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Interaction_RepairGenerator, "Survivor.Ability.Interaction.RepairGenerator");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Interaction_OpenExitDoor, "Survivor.Ability.Interaction.OpenExitDoor");
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_Interaction_HealOther, "Survivor.Ability.Interaction.HealOther");
	// Survivor UseItem Ability
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Ability_UseItem_UseFireCracker, "Survivor.Ability.UseItem.UseFireCracker");
	
	// Survivor Item
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Item_FireCracker, "Survivor.Item.FireCracker");

	// Survivor SetbyCaller
	UE_DEFINE_GAMEPLAY_TAG(Survivor_SetbyCaller_HealAmount, "Survivor.SetbyCaller.HealAmount");

	//Killer
	UE_DEFINE_GAMEPLAY_TAG(Killer_Name_Huntress, "Killer.Name.Huntress");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Name_Nurse, "Killer.Name.Nurse");

	//Killer_Ability
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Attack, "Killer.Common.Ability.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Skill, "Killer.Common.Ability.Skill");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Carry, "Killer.Common.Ability.Interaction.Carry");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Drop, "Killer.Common.Ability.Interaction.Drop");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Hook, "Killer.Common.Ability.Interaction.Hook");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Kick_Totem, "Killer.Common.Ability.Interaction.Kick.Totem");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Kick_Generator, "Killer.Common.Ability.Interaction.Kick.Generator");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Kick_Pallet, "Killer.Common.Ability.Interaction.Kick.Pallet");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Loker, "Killer.Common.Ability.Interaction.Locker");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Hatch, "Killer.Common.Ability.Interaction.Hatch");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Door, "Killer.Common.Ability.Interaction.Door");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Interaction_Window, "Killer.Common.Ability.Interaction.Window");

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
	UE_DEFINE_GAMEPLAY_TAG(Object_Event_Check, "Object.Event.Check");
	UE_DEFINE_GAMEPLAY_TAG(Object_Event_Result_Success, "Object.Event.Result.Success");

	UE_DEFINE_GAMEPLAY_TAG(Object_Event_Result_Failure, "Object.Event.Result.Failure");

	// 방향태그인데 공통으로 써질만 할것같아서 추가했습니다(MMJ)
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
	UE_DEFINE_GAMEPLAY_TAG(Interactable_Character_Survivor, "Interactable.Character.Survivor");
}
