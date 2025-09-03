#include "Shared/DBDGameplayTags.h"

namespace DBDGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Injured, "Survivor.Status.Injured");	
	UE_DEFINE_GAMEPLAY_TAG(Survivor_Status_Crouched, "Survivor.Status.Crouched");	

	//Killer
	UE_DEFINE_GAMEPLAY_TAG(Killer_Name_Huntress, "Killer.Name.Huntress");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Name_Nurse, "Killer.Name.Nurse");

	//Killer_Ability
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_Attack, "Killer.Common.Ability.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Ability_ChargedAttack, "Killer.Common.Ability.ChargedAttack");
	
	//Killer_Status
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Status_Stunned, "Killer.Common.Status.Stunned");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Status_Attacking, "Killer.Common.Status.Attacking");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Status_ChargedAttacking, "Killer.Common.Status.ChargedAttacking");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Common_Status_Falling, "Killer.Common.Status.Falling");
	//Killer_Huntress_Status
	UE_DEFINE_GAMEPLAY_TAG(Killer_Huntress_Status_AxeCharging, "Killer.Huntress.Status.AxeCharging");
	UE_DEFINE_GAMEPLAY_TAG(Killer_Huntress_Status_AxeRefilling, "Killer.Huntress.Status.AxeRefilling");


	// Object
	UE_DEFINE_GAMEPLAY_TAG(Object_Status_IsActive, "Object.Status.IsActive");
	UE_DEFINE_GAMEPLAY_TAG(Object_Status_IsDestroy, "Object.Status.IsDestroy");
	UE_DEFINE_GAMEPLAY_TAG(Object_Status_IsComplete, "Object.Status.IsComplete");

	// Object Progress
	UE_DEFINE_GAMEPLAY_TAG(Object_Progress_Complete, "Object.Progress.Complete");
	UE_DEFINE_GAMEPLAY_TAG(Object_Progress_OnProgress, "Object.Progress.OnProgress");

	// Object SkillChek
	UE_DEFINE_GAMEPLAY_TAG(Object_Event_Check, "Object.Event.Check");
	UE_DEFINE_GAMEPLAY_TAG(Object_Event_Result_Success, "Object.Event.Result.Success");
	UE_DEFINE_GAMEPLAY_TAG(Object_Event_Result_Failure, "Object.Event.Result.Failure");

	// 방향태그인데 공통으로 써질만 할것같아서 추가했습니다(MMJ)
	UE_DEFINE_GAMEPLAY_TAG(Shared_Direction_Front, "Shared.Direction.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Direction_Back, "Shared.Direction.Back");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Direction_Left, "Shared.Direction.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Direction_Right, "Shared.Direction.Right");
}