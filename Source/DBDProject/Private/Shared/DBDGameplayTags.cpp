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
	
}